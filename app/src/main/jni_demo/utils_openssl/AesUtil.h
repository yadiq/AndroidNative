//
// Created by Adi on 2025/1/1.
//

#ifndef ANDROIDNATIVE_AESUTIL_H
#define ANDROIDNATIVE_AESUTIL_H

#include "../utils/Util.h"

class AesUtil {
public:
    /**
     * aes_256_gcm加密函数
     * @param plaintext 明文
     * @return 16进制密文
     */
    static string aes256gcmEncrypt(const void *key, const char *plaintext);
    /**
     * aes_256_gcm解密函数
     * @param ciphertext 密文base64编码
     * @return 明文
     */
    static string aes256gcmDecrypt(const void *key, const char *cipherBase64);

};


#endif //ANDROIDNATIVE_AESUTIL_H