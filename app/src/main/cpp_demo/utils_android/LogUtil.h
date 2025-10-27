//
// Created by Adi on 2024/12/27.
//

#ifndef ANDROIDNATIVE_LOGUTIL_H
#define ANDROIDNATIVE_LOGUTIL_H

#include <android/log.h>

//Android 打印日志
#define DEBUG true
#define LOG_TAG "Native"
#define LOGI(...) if(DEBUG){__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);}
#define LOGD(...) if(DEBUG){__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);}
#define LOGE(...) if(DEBUG){__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);}

#define LOGD_TAG(tag, ...) if(DEBUG){__android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__);} //自定义TAG
#define LOGE_TAG(tag, ...) if(DEBUG){__android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__);} //自定义TAG

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOGD_FILE(...) if(DEBUG){__android_log_print(ANDROID_LOG_DEBUG, __FILENAME__, __VA_ARGS__);} //取文件名当TAG


#endif //ANDROIDNATIVE_LOGUTIL_H
