#ifndef BWL_UTIL_H
#define BWL_UTIL_H

#include "jni.h"
#include <android/log.h>

#define LOG_TAG "Native"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// jstring转为char*
char *jstring2cStr(JNIEnv *env, jstring jstr);

// char*转为jstring
jstring cStr2jstring(JNIEnv *env, const char *pat);

//jbyteArray转为char*
char *jbyteArray2char(JNIEnv *env, jbyteArray byteArray);

//char*转为jbyteArray
jbyteArray char2jbyteArray(JNIEnv *env, char *data, int length);

//// long转为char
//char *jlong2char(JNIEnv *env, jlong number);

// char转为16进制(小写)
void charToHex(unsigned char c, char *hexValue);

// 16进制转为byte[]
void hexStrToUint8(char *str, int strLen, char* dest);

// byte[]转为16进制
void uint8ToHexStr(char *src, int len, char* dest);

//字节数组结尾增加\0
void bytesToStr(char *src, int len, char *dest);

//字符串中删除指定字符
void removeChar(char *src, char value);

//设置随机字符
void setRandomChars(char *str, int len);

//打印bytes
void printBytes(char *src, int len);


#endif //BWL_UTIL_H
