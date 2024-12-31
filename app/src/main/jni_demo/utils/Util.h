#ifndef ANDROIDNATIVE_UTIL_H
#define ANDROIDNATIVE_UTIL_H

#include <string>

using namespace std;

//十六进制字符
#define hex_char "0123456789abcdef" //0123456789ABCDEF
//所有字符
#define all_char "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Util {
public:
    /**
     * byte转hex
     * @param byte
     * @return
     */
    static string byteToHex(char byte);

    /**
     * byte[]转hex
     * @param bytes
     * @param length
     * @return
     */
    static string bytesToHex(char *bytes, int length);

    static string bytesToHex2(char *bytes, int length);

    /**
     * 十六进制字符串转为整数
     * @param hex
     * @return
     */
    static char hexToByte(char *hex);

    /**
     * hex转byte[]
     * @param hex
     * @param length
     * @return
     */
    static string hexToBytes(char *hex, int length);

    /**
     * string删除指定字符
     * @param str
     * @param c
     */
    static string removeChar(string &str, char c);

    /**
     * 设置随机字符
     * @param str 结果
     * @param len 字符长度
     */
    static void setRandomChars(char *str, int len);

    /**
     * 字节数组结尾增加\0
     * @param src
     * @param len
     * @param dest
     */
    static void cstringAdd0(char *src, int len, char *dest);
private:


};

#endif //ANDROIDNATIVE_UTIL_H
