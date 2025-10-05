//
// Created by Adi on 2024/12/31.
//

#ifndef ANDROIDNATIVE_BASE64UTIL_H
#define ANDROIDNATIVE_BASE64UTIL_H

#include "../utils/Util.h"

class Base64Util {
public:
    /**
     * base64加密
     * @param data
     * @param len
     * @return
     */
    static string encode(const char *data, int len);
    /**
     * base64解密
     * @param data
     * @param len
     * @return
     */
    static string decode(const char *data, int len);
};


#endif //ANDROIDNATIVE_BASE64UTIL_H
