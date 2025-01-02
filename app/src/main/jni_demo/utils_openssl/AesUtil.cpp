//
// Created by Adi on 2025/1/1.
//

#include "AesUtil.h"
#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "../utils_android/LogUtil.h"
#include "Base64Util.h"

void handleErrors() {
    LOGD("handleErrors gcm");
}
/////////////////////////////aes_256_gcm/////////////////////////////
//算法地址 https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption

int gcm_encrypt(unsigned char *plaintext, int plaintext_len,
                unsigned char *aad, int aad_len,
                unsigned char *key,
                unsigned char *iv, int iv_len,
                unsigned char *ciphertext,
                unsigned char *tag) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;


    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /* Initialise the encryption operation. */
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        handleErrors();

    /*
     * Set IV length if default 12 bytes (96 bits) is not appropriate
     */
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL))
        handleErrors();

    /* Initialise key and IV */
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv))
        handleErrors();

    /*
     * Provide any AAD data. This can be called zero or more times as
     * required
     */
    if (1 != EVP_EncryptUpdate(ctx, NULL, &len, aad, aad_len))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Normally ciphertext bytes may be written at
     * this stage, but this does not occur in GCM mode
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Get the tag */
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag))
        handleErrors();

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int gcm_decrypt(unsigned char *ciphertext, int ciphertext_len,
                unsigned char *aad, int aad_len,
                unsigned char *tag,
                unsigned char *key,
                unsigned char *iv, int iv_len,
                unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    int ret;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /* Initialise the decryption operation. */
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        handleErrors();

    /* Set IV length. Not necessary if this is 12 bytes (96 bits) */
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL))
        handleErrors();

    /* Initialise key and IV */
    if (!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv))
        handleErrors();

    /*
     * Provide any AAD data. This can be called zero or more times as
     * required
     */
    if (!EVP_DecryptUpdate(ctx, NULL, &len, aad, aad_len))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /* Set expected tag value. Works in OpenSSL 1.0.1d and later */
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag))
        handleErrors();

    /*
     * Finalise the decryption. A positive return value indicates success,
     * anything else is a failure - the plaintext is not trustworthy.
     */
    ret = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    if (ret > 0) {
        /* Success */
        plaintext_len += len;
        return plaintext_len;
    } else {
        /* Verify failed */
        return -1;
    }
}

#define GCM_TAG_SIZE 16

//验证。在线加解密工具
// https://www.lddgo.net/en/encrypt/aes
// 注意；nopadding, 加密结果是 ciphertext + tag

string AesUtil::aes256gcmEncrypt(const char *plaintext, const void *key, const char *iv) {
    unsigned char tag[GCM_TAG_SIZE];
    //加密后密文。密文的长度等于明文长度
    unsigned char ciphertext[strlen(plaintext)];
    int ciphertext_len = gcm_encrypt((unsigned char *) plaintext, strlen(plaintext), NULL, 0, (unsigned char *) key,
                                     (unsigned char *) iv, strlen(iv), ciphertext, tag);
    unsigned char out[ciphertext_len + GCM_TAG_SIZE];
    //加密结果 ciphertext + tag
    memcpy(out, ciphertext, ciphertext_len);
    memcpy(out + ciphertext_len, tag, GCM_TAG_SIZE);
    //bytes转base64
    string base64Str = Base64Util::encode(reinterpret_cast<const char *>(out), sizeof(out));
    return base64Str;
}

string AesUtil::aes256gcmDecrypt(const char *cipherBase64, const void *key, const char *iv) {
    //base64转bytes
    string cipherAll = Base64Util::decode(cipherBase64, strlen(cipherBase64));
    //加密结果 ciphertext + tag
    string ciphertext = cipherAll.substr(0, cipherAll.length() - GCM_TAG_SIZE);
    string tagStr = cipherAll.substr(cipherAll.length() - GCM_TAG_SIZE, GCM_TAG_SIZE);
    //解密后明文。密文的长度等于明文长度
    char plaintext[ciphertext.length()];
    int plaintext_len = gcm_decrypt((unsigned char *) ciphertext.c_str(), ciphertext.length(), NULL, 0,
                                    (unsigned char *) tagStr.c_str(), (unsigned char *) key,
                                    (unsigned char *) iv, strlen(iv), (unsigned char *) plaintext);
    string plainStr(reinterpret_cast<const char *>(plaintext), plaintext_len);
    return plainStr;
}

/////////////////////////////aes_256_cbc/////////////////////////////
//算法地址 https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
int aes_256_cbc_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                        unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int aes_256_cbc_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                        unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

//验证。在线加解密工具
// https://www.lddgo.net/en/encrypt/aes
// 注意；pkcs5padding 或 pkcs7padding

string AesUtil::aes256cbcEncrypt(const char *plaintext, const void *key, const char *iv) {
    int plaintext_len = strlen(plaintext);
    //密文的长度大于等于明文长度，是16的倍数
    char ciphertext[plaintext_len + 16];
    //加密
    int ciphertext_len = aes_256_cbc_encrypt((unsigned char *) (plaintext), plaintext_len,
                                             (unsigned char *) (key),
                                             (unsigned char *) (iv),
                                             (unsigned char *) (ciphertext));
    //bytes转base64
    string base64Str = Base64Util::encode(reinterpret_cast<const char *>(ciphertext), ciphertext_len);
    return base64Str;
}

string AesUtil::aes256cbcDecrypt(const char *cipherBase64, const void *key, const char *iv) {
    //base64转bytes
    string ciphertext = Base64Util::decode(cipherBase64, strlen(cipherBase64));
    //解密后明文。密文的长度大于等于明文长度，是16的倍数
    char plaintext[ciphertext.length()];
    int plaintext_len = aes_256_cbc_decrypt((unsigned char *) (ciphertext.c_str()), ciphertext.length(),
                                            (unsigned char *) (key),
                                            (unsigned char *) (iv),
                                            (unsigned char *) (plaintext));
    string plainStr(reinterpret_cast<const char *>(plaintext), plaintext_len);
    return plainStr;
}

/////////////////////////////aes_128_ecb/////////////////////////////
//算法地址 https://blog.51cto.com/u_15127653/4257952

int aes_128_ecb_encrypt(char *in, int in_len, char *key, char *out) {
    int ret = 0, len = 0, len1 = 0, len2 = 0;
    unsigned char *result = NULL;
    EVP_CIPHER_CTX *ctx;

    ctx = EVP_CIPHER_CTX_new();
    ret = EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, (const unsigned char *) key, NULL);

    if (ret != 1) {
        printf("EVP_EncryptInit_ex error\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    result = (unsigned char *) malloc(AES_BLOCK_SIZE * 64);

    ret = EVP_EncryptUpdate(ctx, result, &len1, (const unsigned char *) in, in_len);

    if (ret != 1) {
        printf("EVP_EncryptUpdate error\n");
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return 0;
    }
    ret = EVP_EncryptFinal_ex(ctx, result + len1, &len2);
    if (ret != 1) {
        printf("EVP_EncryptFinal_ex error\n");
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return 0;
    }

    while (len < (len1 + len2)) {
        out[len] = result[len];
        len++;
    }
    EVP_CIPHER_CTX_free(ctx);
    free(result);
    return (len1 + len2);
}

int aes_128_ecb_decrypt(char *in, int in_len, char *key, char *out) {
    int ret = 0, len = 0, len1 = 0, len2 = 0;
    unsigned char *result = NULL;

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    ret = EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, (const unsigned char *) key, NULL);
    if (ret != 1) {
        printf("EVP_DecryptInit_ex error\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    result = (unsigned char *) malloc(AES_BLOCK_SIZE * 64);

    ret = EVP_DecryptUpdate(ctx, result, &len1, (const unsigned char *) in, in_len);

    if (ret != 1) {
        printf("EVP_DecryptUpdate error\n");
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return 0;
    }
    ret = EVP_DecryptFinal_ex(ctx, result + len1, &len2);
    if (ret != 1) {
        printf("EVP_DecryptFinal_ex error\n");
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return 0;
    }
    while (len < (len1 + len2)) {
        out[len] = result[len];
        len++;
    }
    EVP_CIPHER_CTX_free(ctx);
    free(result);
    return (len1 + len2);
}

//验证。在线加解密工具
// https://www.lddgo.net/en/encrypt/aes
// 注意；pkcs5padding 或 pkcs7padding

string AesUtil::aes128ecbEncrypt(const char *plaintext, const void *key) {
    int plaintext_len = strlen(plaintext);
    //密文的长度大于等于明文长度，是16的倍数
    char ciphertext[plaintext_len + 16];
    //加密
    int ciphertext_len = aes_128_ecb_encrypt((char *) plaintext, plaintext_len, (char *) key, ciphertext);
    //bytes转base64
    string base64Str = Base64Util::encode(reinterpret_cast<const char *>(ciphertext), ciphertext_len);
    return base64Str;
}

string AesUtil::aes128ecbDecrypt(const char *cipherBase64, const void *key) {
    //base64转bytes
    string ciphertext = Base64Util::decode(cipherBase64, strlen(cipherBase64));
    //解密后明文。密文的长度大于等于明文长度，是16的倍数
    char plaintext[ciphertext.length()];
    int plaintext_len = aes_128_ecb_decrypt((char *) (ciphertext.c_str()), ciphertext.length(), (char *) (key),
                                            plaintext);
    string plainStr(reinterpret_cast<const char *>(plaintext), plaintext_len);
    return plainStr;
}