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





void hexStrToUint8(char *str, int strLen, char* dest) {
    unsigned int val;
      for(int i = 0; i < strLen; i += 2){
        sscanf(str + i, "%02x", &val);
        dest[i / 2] = val;
      }
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

