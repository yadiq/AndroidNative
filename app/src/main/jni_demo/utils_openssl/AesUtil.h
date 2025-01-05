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
     * @return 密文base64编码
     */
    static string aes256gcmEncrypt(const char *plaintext, const void *key, const char *iv);
    /**
     * aes_256_gcm解密函数
     * @param ciphertext 密文base64编码
     * @return 明文
     */
    static string aes256gcmDecrypt(const char *cipherBase64, const void *key, const char *iv);

    /**
     * aes_256_cbc加密函数
     * @param plaintext 明文
     * @return 密文base64编码
     */
    static string aes256cbcEncrypt(const char *plaintext, const void *key, const char *iv);
    /**
     * aes_256_cbc解密函数
     * @param ciphertext 密文base64编码
     * @return 明文
     */
    static string aes256cbcDecrypt(const char *cipherBase64, const void *key, const char *iv);

    /**
     * aes_128_ecb加密函数
     * @param plaintext 明文
     * @return 密文base64编码
 */
    static string aes128ecbEncrypt(const char *plaintext, const void *key);
    /**
     * aes_128_ecb解密函数
     * @param ciphertext 密文base64编码
     * @return 明文
     */
    static string aes128ecbDecrypt(const char *cipherBase64, const void *key);

};


#endif //ANDROIDNATIVE_AESUTIL_H
