/* Simple AES GCM test program, uses the same NIST data used for the FIPS
 * self test but uses the application level EVP APIs.
 */

#include <stdio.h>
#include <string.h>

#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"

#include "../utils/Util.h"
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

#define GCM_IV_SIZE 12
#define GCM_TAG_SIZE 16

/**
 * aes_256_gcm加密函数
 * @param plaintext 明文字符串
 * @return 密文16进制，需要手动释放空间
 */
char *aes256gcm_encrypt(const void *key, const unsigned char *plaintext) {
    int plaintext_len = strlen((const char *) plaintext);

    //生成初始化向量
    unsigned char iv[GCM_IV_SIZE];//12B 随机数
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        LOGD("Error generating GCM IV.\n");
    }
    //unsigned char iv[13] = "123456789012";TODO

    int iv_len = GCM_IV_SIZE;
    unsigned char tag[GCM_TAG_SIZE];
    int tag_len = GCM_TAG_SIZE;
    //加密后密文
    unsigned char ciphertext[plaintext_len];
    int ciphertext_len = gcm_encrypt((unsigned char *) plaintext, plaintext_len, NULL, 0, (unsigned char *) key, iv,
                                     iv_len, ciphertext, tag);
    unsigned char out[iv_len + ciphertext_len + tag_len];
    //加密结果 iv + ciphertext + tag
    memcpy(out, iv, iv_len);
    memcpy(out + iv_len, ciphertext, ciphertext_len);
    memcpy(out + iv_len + ciphertext_len, tag, tag_len);
    //bytes转hex
    /*char *hexStr = (char *) malloc(sizeof(out) * 2 + 1);//存储在堆区，由程序员分配释放
    uint8ToHexStr((char *) out, sizeof(out), hexStr);
    return hexStr;*/
    //bytes转base64
    char *base64Str = (char *) malloc((sizeof(out) + 2) / 3 * 4 + 1);//存储在堆区，由程序员分配释放
    int base64Len = base64_encode(reinterpret_cast<char *>(out), sizeof(out), base64Str);
    return base64Str;
}

/**
 * aes_256_gcm解密函数
 * @param inHex 密文base64编码
 * @return 明文字符串，需要手动释放空间
 */
char *aes256gcm_decrypt(const void *key, const unsigned char *inEncode) {
    int inEncode_len = strlen((const char *) inEncode);
    //hex转bytes
    /*int in_len = inEncode_len / 2;
    unsigned char in[in_len];
    hexStrToUint8((char *) inEncode, inEncode_len, (char *) in);*/
    //base64转bytes
    unsigned char in[inEncode_len];
    int in_len = base64_decode((char *) inEncode, inEncode_len, reinterpret_cast<char *>(in));

    //加密结果 iv + ciphertext + tag
    unsigned char iv[GCM_IV_SIZE];//12B 随机数
    int iv_len = GCM_IV_SIZE;
    unsigned char tag[GCM_TAG_SIZE];
    int tag_len = GCM_TAG_SIZE;
    int ciphertext_len = in_len - iv_len - tag_len;
    unsigned char ciphertext[ciphertext_len];
    //读取iv
    memcpy(iv, in, iv_len);
    //读取ciphertext
    memcpy(ciphertext, in + iv_len, ciphertext_len);
    //读取tag
    memcpy(tag, in + iv_len + ciphertext_len, tag_len);
    //解密后明文
    /*unsigned char plaintext[ciphertext_len];
    int plaintext_len = gcm_decrypt(ciphertext, ciphertext_len, NULL, 0, tag, (unsigned char *)key, iv, iv_len, plaintext);
    //转hex,改为base64编码
    char *hexStr = (char *) malloc(plaintext_len * 2 + 1);//存储在堆区，由程序员分配释放
    uint8ToHexStr((char *) plaintext, plaintext_len, hexStr);
    return hexStr;*/
    char *plaintext = (char *) malloc(ciphertext_len + 1);//存储在堆区，由程序员分配释放
    int plaintext_len = gcm_decrypt(ciphertext, ciphertext_len, NULL, 0, tag, (unsigned char *) key, iv, iv_len,
                                    (unsigned char *) plaintext);
    plaintext[plaintext_len] = '\0';
    return plaintext;
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

/**
 * aes_128_ecb加密函数
 * @param plaintext 明文字符串
 * @return
 */
char *aes128ecb_encrypt(char *key, char *plaintext) {
    int plaintext_len = strlen(plaintext);
    //密文的长度大于等于明文长度，是16的倍数
    char ciphertext[plaintext_len + 16];
    //加密
    int ciphertext_len = aes_128_ecb_encrypt(plaintext, plaintext_len, key, ciphertext);
    //bytes转base64
    char *base64Str = (char *) malloc((ciphertext_len + 2) / 3 * 4 + 1);//存储在堆区，由程序员分配释放
    int base64Len = base64_encode(ciphertext, ciphertext_len, base64Str);
    return base64Str;
}

/**
 * aes_128_ecb解密函数
 * @param inHex 密文base64编码
 * @return 明文字符串，需要手动释放空间
 */
char *aes128ecb_decrypt(char *key, char *inHex) {
    int inEncode_len = strlen((const char *) inHex);
    //base64转bytes
    char in[inEncode_len];
    int in_len = base64_decode(inHex, inEncode_len, in);

    //密文的长度大于等于明文长度，是16的倍数
    char *plaintext = (char *) malloc(in_len + 1);//存储在堆区，由程序员分配释放
    int plaintext_len = aes_128_ecb_decrypt(in, in_len, key, plaintext);
    plaintext[plaintext_len] = '\0';
    return plaintext;
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

/**
 * aes_128_ecb加密函数
 * @param plaintext 明文字符串
 * @return
 */
char *aes256cbc_encrypt(char *key, char *iv, char *plaintext) {
    int plaintext_len = strlen(plaintext);
    //密文的长度大于等于明文长度，是16的倍数
    char ciphertext[plaintext_len + 16];
    //加密
    int ciphertext_len = aes_256_cbc_encrypt(reinterpret_cast<unsigned char *>(plaintext), plaintext_len,
                                             reinterpret_cast<unsigned char *>(key),
                                             reinterpret_cast<unsigned char *>(iv),
                                             reinterpret_cast<unsigned char *>(ciphertext));
    //bytes转base64
    char *base64Str = (char *) malloc((ciphertext_len + 2) / 3 * 4 + 1);//存储在堆区，由程序员分配释放
    int base64Len = base64_encode(ciphertext, ciphertext_len, base64Str);
    return base64Str;
}

/**
 * aes_256_cbc解密函数
 * @param inHex 密文base64编码
 * @return 明文字符串，需要手动释放空间
 */
char *aes256cbc_decrypt(char *key, char *iv, char *inHex) {
    int inEncode_len = strlen((const char *) inHex);
    //base64转bytes
    char in[inEncode_len];
    int in_len = base64_decode(inHex, inEncode_len, in);

    //密文的长度大于等于明文长度，是16的倍数
    char *plaintext = (char *) malloc(in_len + 1);//存储在堆区，由程序员分配释放
    int plaintext_len = aes_256_cbc_decrypt(reinterpret_cast<unsigned char *>(in), in_len,
                                            reinterpret_cast<unsigned char *>(key),
                                            reinterpret_cast<unsigned char *>(iv),
                                            reinterpret_cast<unsigned char *>(plaintext));
    plaintext[plaintext_len] = '\0';
    return plaintext;
}