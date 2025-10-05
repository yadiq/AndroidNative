//
// Created by Adi on 2024/12/31.
// base64编码
// 原理：将字符串以每3个8比特(bit)的字节子序列拆分成4个6比特(bit)的字节子序列
// 编码前长度 N
// 编码后长度 (N + 2)/3*4

#include "Base64Util.h"

#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"


string Base64Util::encode(const char *data, int len) {
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, data, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);

    string result(bptr->data, bptr->length);
    //base64中可能有 \n, 需要去掉
    result = Util::removeChar(result, '\n');

    BIO_free_all(bio);
    return result;
}

string Base64Util::decode(const char *data, int len) {
    BIO *b64, *bio;
    char cstr[len];

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf(data, len);
    bio = BIO_push(b64, bio);

    int size = BIO_read(bio, cstr, len);
    string result(cstr, size);
    BIO_free_all(bio);
    return result;
}
