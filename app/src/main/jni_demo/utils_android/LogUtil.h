//
// Created by Adi on 2024/12/27.
//

#ifndef ANDROIDNATIVE_LOGUTIL_H
#define ANDROIDNATIVE_LOGUTIL_H

#include <android/log.h>

//Android 打印日志
#define LOG_TAG "Native"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //ANDROIDNATIVE_LOGUTIL_H
