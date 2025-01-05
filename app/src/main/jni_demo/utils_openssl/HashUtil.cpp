//
// Created by guoya on 2025/1/2.
//
#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "HashUtil.h"

//在线加解密 https://tool.oschina.net/encrypt?type=2
//SHA-1可以生成一个被称为消息摘要的160位（20字节）散列值。加密后20B
//Sha1加密是不可逆的，网上虽然有解密的方法，但只能解密很简单的密码
string HashUtil::sha1Encrypt(const char *plaintext) {
    char md[20];
    SHA1(reinterpret_cast<const unsigned char *>(plaintext), strlen(plaintext), reinterpret_cast<unsigned char *>(md));
    //转hex
    string mdHex = Util::bytesToHex(md, sizeof(md));
    return mdHex;
}

//HMAC算法
//hmac("SHA1", msg, key);
//hmac("SHA224", msg, key);
//hmac("SHA256", msg, key);
//hmac("SHA384", msg, key);
//hmac("SHA512", msg, key);
//hmac("MD5", msg, key);
string HashUtil::hmacEncrypt(const char *algorithm, const char *plaintext, const char *key) {
    const EVP_MD *md = EVP_get_digestbyname(algorithm);
    if (md == NULL) {
        return "";
    }
    unsigned char md_value[EVP_MAX_MD_SIZE] = "";
    unsigned int md_len = 0;

#if !defined(OPENSSL_VERSION_NUMBER) || OPENSSL_VERSION_NUMBER < 0x10100000L
    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, keyLen, md, NULL);
    HMAC_Update(&ctx, msg, msgLen);
    HMAC_Final(&ctx, md_value, &md_len);
    HMAC_CTX_cleanup(&ctx);
#else
    HMAC_CTX *ctx;
    ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, strlen(key), md, NULL);
    HMAC_Update(ctx, reinterpret_cast<const unsigned char *>(plaintext), strlen(plaintext));
    HMAC_Final(ctx, md_value, &md_len);
    HMAC_CTX_free(ctx);
#endif

    //转hex
    string mdHex = Util::bytesToHex(reinterpret_cast<char *>(md_value), md_len);
    return mdHex;
}