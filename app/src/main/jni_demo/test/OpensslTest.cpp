//
// Created by Adi on 2024/12/31.
//

#include <string>

#include "OpensslTest.h"
#include "../utils_openssl/Base64Util.h"
#include "../utils_android/LogUtil.h"
#include "../utils_openssl/AesUtil.h"

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
    const char *key = "UY_R+2-3YJwfi*Kbs!E93NW(cF-WjuNX";
    const char *iv = "123456789012";
    string aes256gcmEncrypt = AesUtil::aes256gcmEncrypt(str, key, iv);
    LOGD("aes256gcmEncrypt: %s", aes256gcmEncrypt.c_str());
    string aes256gcmDecrypt = AesUtil::aes256gcmDecrypt(aes256gcmEncrypt.c_str(), key, iv);
    LOGD("aes256gcmDecrypt: %s", aes256gcmDecrypt.c_str());
}
