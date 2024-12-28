//
// 工具类
//

#include "Util.h"


string Util::cstringToHex(char *cstr, int length) {
    string str("");
    for (int i = 0; i < length; i++) {
        //append(n, c)，在字符串后面添加n个字符
        str.append(1, hex_char[(*(cstr + i)) >> 4]);
        str.append(1, hex_char[(*(cstr + i)) & 0x0f]);
    }
    return str;
}

//TODO
string Util::hexTostring(string hex) {
    return std::string();
}

string Util::removeChar(string str, char c) {
    //使用 erase 和 remove 配合
    //运行remove后, 容器的[first, newEnd)内的元素为所有未被删除的元素, [newEnd, end)之间的元素已经没用了.
    //再运行erase, 清空[newEnd, end)之间的元素
    str.erase(remove(str.begin(), str.end(), c), str.end());
    return str;
}

//string => bytes
//https://blog.csdn.net/weixin_52402390/article/details/122407222
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


