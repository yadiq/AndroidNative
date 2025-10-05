//
// Created by Adi on 2024/12/31.
//

#include <string>

#include "OpensslTest.h"
#include "../utils_openssl/Base64Util.h"
#include "../utils_android/LogUtil.h"
#include "../utils_openssl/AesUtil.h"
#include "../utils_openssl/HashUtil.h"

using namespace std;

void OpensslTest::base64() {
    string str = "123abc";
    string base64Encode = Base64Util::encode(str.c_str(), str.length());
    LOGD("base64Encode: %s", base64Encode.c_str());
    string base64Decode = Base64Util::decode(base64Encode.c_str(), base64Encode.length());
    LOGD("base64Decode: %s", base64Decode.c_str());
}

void OpensslTest::aes() {
    const char *str = "123abc";
    const char *key256 = "12345678901234567890123456789012";
    const char *key128 = "1234567890123456";
    const char *iv = "1234567890123456";

    string aes256gcmEncrypt = AesUtil::aes256gcmEncrypt(str, key256, iv);
    LOGD("aes256gcmEncrypt: %s", aes256gcmEncrypt.c_str());
    string aes256gcmDecrypt = AesUtil::aes256gcmDecrypt(aes256gcmEncrypt.c_str(), key256, iv);
    LOGD("aes256gcmDecrypt: %s", aes256gcmDecrypt.c_str());

    string aes256cbcEncrypt = AesUtil::aes256cbcEncrypt(str, key256, iv);
    LOGD("aes256cbcEncrypt: %s", aes256cbcEncrypt.c_str());
    string aes256cbcDecrypt = AesUtil::aes256cbcDecrypt(aes256cbcEncrypt.c_str(), key256, iv);
    LOGD("aes256cbcDecrypt: %s", aes256cbcDecrypt.c_str());

    string aes128ecbEncrypt = AesUtil::aes128ecbEncrypt(str, key128);
    LOGD("aes128ecbEncrypt: %s", aes128ecbEncrypt.c_str());
    string aes128ecbDecrypt = AesUtil::aes128ecbDecrypt(aes128ecbEncrypt.c_str(), key128);
    LOGD("aes128ecbDecrypt: %s", aes128ecbDecrypt.c_str());
}

void OpensslTest::sha() {
    const char *str = "123abc";
    const char *key256 = "12345678901234567890123456789012";

    string sha1Encrypt = HashUtil::sha1Encrypt(str);
    LOGD("sha1Encrypt: %s", sha1Encrypt.c_str());

    string hmacSHA256Encrypt = HashUtil::hmacEncrypt("SHA256", str, key256);
    LOGD("hmacSHA256Encrypt: %s", hmacSHA256Encrypt.c_str());
}
