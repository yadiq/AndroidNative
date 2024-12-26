//
// 工具类
// 打印日志，类型转换
//

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "jni.h"
#include "UtilOld.h"

#define HEX_VALUES "0123456789abcdef"
//#define HEX_VALUES "0123456789ABCDEF"
//所有字符
const unsigned char allChar[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


char *jstring2cStr(JNIEnv *env, jstring jstr) {
    const char *temp = (char *) env->GetStringUTFChars(jstr, NULL);
    char *ret = (char *) malloc(strlen(temp) + 1);
    strcpy(ret, temp);
    env->ReleaseStringUTFChars(jstr, temp);
    return ret;
}

jstring cStr2jstring(JNIEnv *env, const char *chars) {
    jstring ret = env->NewStringUTF(chars);
    return ret;
}

char *jbyteArray2char(JNIEnv *env, jbyteArray byteArray) {
    jbyte *byte = env->GetByteArrayElements(byteArray, 0);
    int chars_len = env->GetArrayLength(byteArray);
    /*char *chars = new char[chars_len + 1];
    memset(chars,0,chars_len + 1);//将指定的值 c 复制到 str 所指向的内存区域的前 n 个字节中
    memcpy(chars, byte, chars_len);//从存储区 str2 复制 n 个字节到存储区 str1
    chars[chars_len] = 0;*/
    char *chars = (char *) malloc(chars_len);
    memcpy(chars, byte, chars_len);
    env->ReleaseByteArrayElements(byteArray, byte, 0);
    return chars;
}

jbyteArray char2jbyteArray(JNIEnv *env, char *data, int length) {
    jbyte *byte = (jbyte *) data;
    jbyteArray byteArray = env->NewByteArray(length);
    env->SetByteArrayRegion(byteArray, 0, length, byte);
    return byteArray;
}

/*char *jlong2char(JNIEnv *env, jlong number) {
    char *chars = (char *) malloc(20);
    sprintf(chars, "%lld", number);
    return chars;
}*/

/**
 * char转为16进制(小写)
 * @param c
 * @param hexValue
 */
void charToHex(unsigned char c, char *hexValue) {
    if (c < 16) {
        hexValue[0] = HEX_VALUES[0];
        hexValue[1] = HEX_VALUES[c];
    } else {
        int l = c / 16;
        int r = c % 16;
        hexValue[0] = HEX_VALUES[l];
        hexValue[1] = HEX_VALUES[r];
    }
    hexValue[2] = 0;
}

void hexStrToUint8(char *str, int strLen, char* dest) {
    unsigned int val;
      for(int i = 0; i < strLen; i += 2){
        sscanf(str + i, "%02x", &val);
        dest[i / 2] = val;
      }
}

void uint8ToHexStr(char *src, int len, char* dest) {
    for(int i = 0; i < len; i++ ){
      sprintf(&dest[i * 2], "%02x", (unsigned char)src[i]);
    }
    dest[len * 2] = '\0';
}

/**
 * 字节数组结尾增加\0
 * @param src
 * @param len
 * @param dest
 */
void bytesToStr(char *src, int len, char *dest) {
    memcpy(dest, src, len);
    dest[len] = 0;
}

/**
 * 字符串中删除指定字符
 * @param src
 * @param value
 */
void removeChar(char *str, char value) {
    int len = strlen(str);
    for (int i = 0; i < len;) {
        if (str[i] == value) {
            for (int j = i + 1; j < len; j++) {
                str[j - 1] = str[j];
            }
            str[len - 1] = '\0';
        } else {
            i++;
        }
    }
}

/**
 * 设置随机字符
 * @param str 结果
 * @param len 字符长度
 */
void setRandomChars(char *str, int len) {
    //srand((unsigned) time(NULL));//初始化随机数发生器
    for (int i = 0; i < len; i++) {
        str[i] = allChar[rand() % 62];
    }
}

/**
 * 打印字节数组，十六进制
 * @param src
 * @param len
 */
void printBytes(char *src, int len) {
    char dest[len * 2 + 1];
    for(int i = 0; i < len; i++ ){
        sprintf(&dest[i * 2], "%02x", (unsigned char)src[i]);
    }
    dest[len * 2] = '\0';
    LOGD("printBytes= %s", dest);
}

