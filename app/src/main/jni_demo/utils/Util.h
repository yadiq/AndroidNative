#ifndef ANDROIDNATIVE_UTIL_H
#define ANDROIDNATIVE_UTIL_H

#include <string>

using namespace std;

//十六进制字符
#define hex_char "0123456789abcdef" //0123456789ABCDEF
//所有字符
#define all_char = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

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
    static string removeChar(string str, char c);
private:


};

#endif //ANDROIDNATIVE_UTIL_H
