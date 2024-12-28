//
// 工具类
//

#include "Util.h"

string Util::byteToHex(char byte) {
    string str;
    str.append(1, hex_char[byte >> 4]);
    str.append(1, hex_char[byte & 0x0f]);
    return str;
}

string Util::bytesToHex(char *bytes, int length) {
    string str;
    for (int i = 0; i < length; i++) {
        str.append(byteToHex(*(bytes + i)));
    }
    return str;
}

string Util::bytesToHex2(char *bytes, int length) {
    char dest[length * 2];
    for (int i = 0; i < length; i++) {
        sprintf(&dest[i * 2], "%02x", (unsigned char) bytes[i]);
    }
    string str(dest, length * 2);
    return str;
}

//将字符串转为整数
//atoi、stoi、strtol的区别
//		atoi()和strtol()都是c里面的函数，他们都可以将字符串转为int，他们都从字符串开始寻找数字、符号，然后遇到非法字符终止(小数点是非法字符)，不会报错。
//		atoi()只能识别十进制的，而strtol()第三个参数可以设置进制。
//		stoi()则是string库中的函数，它的参数是string
char Util::hexToByte(char *hex) {
    char byte = (char) strtol(hex, nullptr, 16);
    return byte;
}

string Util::hexToBytes(char *hex, int length) {
    char dest[length / 2];
    unsigned int val;
    for (int i = 0; i < length; i += 2) {
        sscanf(hex + i, "%02x", &val);
        dest[i / 2] = val;
    }
    string str(dest, length / 2);
    return str;
}

string Util::removeChar(string str, char c) {
    //使用 erase 和 remove 配合
    //运行remove后, 容器的[first, newEnd)内的元素为所有未被删除的元素, [newEnd, end)之间的元素已经没用了.
    //再运行erase, 清空[newEnd, end)之间的元素
    str.erase(remove(str.begin(), str.end(), c), str.end());
    return str;
}

void Util::setRandomChars(char *str, int len) {
    //srand((unsigned) time(NULL));//初始化随机数发生器
    for (int i = 0; i < len; i++) {
        str[i] = all_char[rand() % 62];
    }
}
/////////////////////////old////////////////////////
///**
// * 字节数组结尾增加\0
// * @param src
// * @param len
// * @param dest
// */
//void bytesToStr(char *src, int len, char *dest) {
//    memcpy(dest, src, len);
//    dest[len] = 0;
//}
//
///**
// * 设置随机字符
// * @param str 结果
// * @param len 字符长度
// */
//void setRandomChars(char *str, int len) {
//    //srand((unsigned) time(NULL));//初始化随机数发生器
//    for (int i = 0; i < len; i++) {
//        str[i] = all_char[rand() % 62];
//    }
//}
//
///**
// * 打印字节数组，十六进制
// * @param src
// * @param len
// */
//void printBytes(char *src, int len) {
//    char dest[len * 2 + 1];
//    for (int i = 0; i < len; i++) {
//        sprintf(&dest[i * 2], "%02x", (unsigned char) src[i]);
//    }
//    dest[len * 2] = '\0';
//    //LOGD("printBytes= %s", dest);
//}


