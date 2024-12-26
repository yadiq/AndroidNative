#ifndef ANDROIDNATIVE_UTIL_H
#define ANDROIDNATIVE_UTIL_H

#include <android/log.h>
#include <string>
#include "jni.h"

//Android 打印日志
#define LOG_TAG "Native"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//十六进制字符
#define hex_table "0123456789abcdef"
//#define hex_table "0123456789ABCDEF"
//所有字符
const unsigned char ALL_CHAR[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


class Util {
public:
    //数据类型转换
    /**
     * jstring 转 std::string
     * @param env
     * @param jstr
     * @return
     */
    static std::string jstringTocstring(JNIEnv *env, jstring jstr);//可以返回string, 需要将结果赋值到string

    /**
     * std::string 转 jstring
     * @param env
     * @param cstr
     * @return
     */
    static jstring cstringTojstring(JNIEnv *env, std::string cstr);

    /**
     * byte[]转hex (小写)
     * @param bytes
     * @param length
     * @return
     */
    static std::string bytesToHex(char *bytes, int length);

private:

};

#endif //ANDROIDNATIVE_UTIL_H
