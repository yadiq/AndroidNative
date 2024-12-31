//
// Created by Adi on 2024/12/31.
//

#include <string>

#include "OpensslTest.h"
#include "../utils_openssl/Base64Util.h"
#include "../utils_android/LogUtil.h"

using namespace std;

void OpensslTest::base64() {
    string str = "123abc";
    string base64Encode = Base64Util::encode(str.c_str(), str.length());
    LOGD("base64Encode: %s", base64Encode.c_str());
    string base64Decode = Base64Util::decode(base64Encode.c_str(), base64Encode.length());
    LOGD("base64Decode: %s", base64Decode.c_str());
}
