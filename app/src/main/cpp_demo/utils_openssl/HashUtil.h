//
// Created by guoya on 2025/1/2.
//

#ifndef ANDROIDNATIVE_HASHUTIL_H
#define ANDROIDNATIVE_HASHUTIL_H

#include "../utils/Util.h"

class HashUtil {
public:
    /**
     * SHA1加密
     * @param plaintext 明文
     * @return 密文转十六进制字符串
     */
    static string sha1Encrypt(const char *plaintext);

    /**
     * HMAC加密
     * @param algorithm 哈希算法名称：MD5、SHA1、SHA224、SHA256、SHA384、SHA512
     * @param plaintext 明文
     * @param key 密钥
     * @return 密文转十六进制字符串
     */
    static string hmacEncrypt(const char *algorithm, const char *plaintext, const char *key);
};

#endif //ANDROIDNATIVE_HASHUTIL_H
