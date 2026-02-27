//
// Created by gyd on 2026/2/25.
//

#include "Player.h"
#include "../utils_android/LogUtil.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

void ffmpeg_log_callback(void *ptr, int level, const char *fmt, va_list vl) {
    if (level <= AV_LOG_DEBUG) { // 控制输出级别
        char line[1024];
        vsnprintf(line, sizeof(line), fmt, vl);
        LOGD("ffmpeg_log: %s", line)
        //__android_log_print(ANDROID_LOG_DEBUG, "FFmpeg", "%s", line);
    }
}

void Player::setSurface(JNIEnv *env, jobject surface) {
    window = ANativeWindow_fromSurface(env, surface);
}

void Player::start(const char *url) {

    isPlaying = true;

    decodeThread = std::thread([=]() {

        //FFmpeg 调试日志
        av_log_set_level(AV_LOG_DEBUG);
        av_log_set_callback(ffmpeg_log_callback);

        //初始化网络
        av_register_all();
        avformat_network_init();

        //网络缓冲和延迟
        AVDictionary *opts = NULL;
        av_dict_set(&opts, "rtmp_live", "live", 0);   // 用于直播拉流
        av_dict_set(&opts, "max_delay", "500000", 0); // 最大延迟 0.5s
        av_dict_set(&opts, "buffer_size", "1024000", 0); // TCP buffer 1MB
//        AVDictionary *opts = nullptr;
//        av_dict_set(&opts, "fflags", "nobuffer", 0);
//        av_dict_set(&opts, "rtmp_live", "live", 0);
//        av_dict_set(&opts, "max_delay", "0", 0);      // 单位微秒
//        av_dict_set(&opts, "timeout", "5000000", 0);  // 5秒超时
//        av_dict_set(&opts, "buffer_size", "1024000", 0);
//        av_dict_set(&opts, "rtmp_transport", "tcp", 0); //强制使用 TCP
        av_dict_set(&opts, "rtmp_buffer", "1000", 0); // buffer 1s
        av_dict_set(&opts, "stimeout", "5000000", 0);  // 5s 超时
        av_dict_set(&opts, "fflags", "nobuffer", 0);
        av_dict_set(&opts, "flags", "low_delay", 0);

        LOGD("avformat_open_input: %s", url);
        AVFormatContext *fmt = nullptr;
        int ret = avformat_open_input(&fmt, url, nullptr, &opts);
        if (ret < 0) {
            char errbuf[256];
            av_strerror(ret, errbuf, sizeof(errbuf));
            LOGE("avformat_open_input failed: %s", errbuf);
            return;
        }

        avformat_find_stream_info(fmt, nullptr);

        int videoIndex = -1;

        for (int i = 0; i < fmt->nb_streams; i++) {
            if (fmt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoIndex = i;
                break;
            }
        }

        AVCodecParameters *codecpar = fmt->streams[videoIndex]->codecpar;
        const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
        AVCodecContext *codecCtx = avcodec_alloc_context3(codec);

        avcodec_parameters_to_context(codecCtx, codecpar);
        //设置多线程解码 TODO
        codecCtx->thread_count = 4;             // 根据设备 CPU 核数设置，一般 2~4 就够
        codecCtx->thread_type  = FF_THREAD_FRAME; // FF_THREAD_FRAME 推荐用于视频帧解码

        avcodec_open2(codecCtx, codec, nullptr);

        AVPacket *packet = av_packet_alloc();
        AVFrame *frame = av_frame_alloc();

        SwsContext *swsCtx = sws_getContext(
                codecCtx->width,
                codecCtx->height,
                codecCtx->pix_fmt,
                codecCtx->width,
                codecCtx->height,
                AV_PIX_FMT_RGBA,
                SWS_BILINEAR,
                nullptr, nullptr, nullptr);

        uint8_t *dstData[4];
        int dstLinesize[4];

        av_image_alloc(dstData, dstLinesize,
                       codecCtx->width,
                       codecCtx->height,
                       AV_PIX_FMT_RGBA,
                       1);

        ANativeWindow_setBuffersGeometry(window,
                                         codecCtx->width,
                                         codecCtx->height,
                                         WINDOW_FORMAT_RGBA_8888);

        while (isPlaying && av_read_frame(fmt, packet) >= 0) {

            if (packet->stream_index == videoIndex) {

                avcodec_send_packet(codecCtx, packet);

                while (avcodec_receive_frame(codecCtx, frame) == 0) {

                    sws_scale(swsCtx,
                              frame->data,
                              frame->linesize,
                              0,
                              codecCtx->height,
                              dstData,
                              dstLinesize);

                    ANativeWindow_Buffer buffer;

                    ANativeWindow_lock(window, &buffer, nullptr);

                    memcpy(buffer.bits,
                           dstData[0],
                           codecCtx->width * codecCtx->height * 4);

                    ANativeWindow_unlockAndPost(window);
                }
            }

            av_packet_unref(packet);
        }

        avcodec_free_context(&codecCtx);
        avformat_close_input(&fmt);
    });

    decodeThread.detach();
}

void Player::stop() {
    isPlaying = false;
}
