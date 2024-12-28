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
     * char* 转 hex (小写)
     * @param bytes
     * @param length
     * @return
     */
    static string cstringToHex(char *bytes, int length);

    static string hexTostring(string hex);
    /**
     * string删除指定字符
     * @param str
     * @param c
     */
    static string removeChar(string str, char c);
private:

};

#endif //ANDROIDNATIVE_UTIL_H
