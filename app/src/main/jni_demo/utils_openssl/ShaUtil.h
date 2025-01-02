//
// Created by guoya on 2025/1/2.
//

#ifndef ANDROIDNATIVE_SHAUTIL_H
#define ANDROIDNATIVE_SHAUTIL_H

#include "../utils/Util.h"

class ShaUtil {
public:
    /**
     * SHA1加密
     * @param plaintext
     * @return 16进制字符串
     */
    static string sha1Encrypt(const char *plaintext);

    /**
     * HMAC加密
     * @param plaintext
     * @param key
     * @return 16进制字符串
     */
    static string hmacEncrypt(const char *algorithm, const char *plaintext, const char *key);
};

#endif //ANDROIDNATIVE_SHAUTIL_H
