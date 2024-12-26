//
// 工具类
//

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "jni.h"
#include "Util.h"


std::string Util::jstringTocstring(JNIEnv *env, jstring jstr) {
    const char *str = (char *) env->GetStringUTFChars(jstr, NULL);
    std::string cstr = str;
    env->ReleaseStringUTFChars(jstr, str);
    return cstr;
}

jstring Util::cstringTojstring(JNIEnv *env, std::string cstr) {
    jstring jstr = env->NewStringUTF(cstr.c_str());
    return jstr;
}

std::string Util::bytesToHex(char* bytes, int length) {
    std::string str("");
    for (int i = 0; i < length; i++) {
        str.append(1, hex_table[(*(bytes + i)) >> 4]);//在字符串后面添加1个字符
        str.append(1, hex_table[(*(bytes + i)) & 0x0f]);
    }
    return str;
}

/*char *jbyteArray2char(JNIEnv *env, jbyteArray byteArray) {
    jbyte *byte = env->GetByteArrayElements(byteArray, 0);
    int chars_len = env->GetArrayLength(byteArray);
    *//*char *chars = new char[chars_len + 1];
    memset(chars,0,chars_len + 1);//将指定的值 c 复制到 str 所指向的内存区域的前 n 个字节中
    memcpy(chars, byte, chars_len);//从存储区 str2 复制 n 个字节到存储区 str1
    chars[chars_len] = 0;*//*
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
}*/


/*void hexStrToUint8(char *str, int strLen, char* dest) {
    unsigned int val;
      for(int i = 0; i < strLen; i += 2){
        sscanf(str + i, "%02x", &val);
        dest[i / 2] = val;
      }
}


*//**
 * 字节数组结尾增加\0
 * @param src
 * @param len
 * @param dest
 *//*
void bytesToStr(char *src, int len, char *dest) {
    memcpy(dest, src, len);
    dest[len] = 0;
}

*//**
 * 字符串中删除指定字符
 * @param src
 * @param value
 *//*
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

*//**
 * 设置随机字符
 * @param str 结果
 * @param len 字符长度
 *//*
void setRandomChars(char *str, int len) {
    //srand((unsigned) time(NULL));//初始化随机数发生器
    for (int i = 0; i < len; i++) {
        str[i] = allChar[rand() % 62];
    }
}

*//**
 * 打印字节数组，十六进制
 * @param src
 * @param len
 *//*
void printBytes(char *src, int len) {
    char dest[len * 2 + 1];
    for(int i = 0; i < len; i++ ){
        sprintf(&dest[i * 2], "%02x", (unsigned char)src[i]);
    }
    dest[len * 2] = '\0';
    LOGD("printBytes= %s", dest);
}*/


