//
// Created by Adi on 2024/12/27.
//
#include <limits>

#include "TypeTest.h"
#include "../utils_android/LogUtil.h"
#include "../utils/Util.h"


void TypeTest::pintTypeSize() {
    LOGD("bool 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(bool), numeric_limits<bool>::max(),
         numeric_limits<bool>::min());
    LOGD("char 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(char), numeric_limits<char>::max(),
         numeric_limits<char>::min());
    LOGD("int 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(int), numeric_limits<int>::max(),
         numeric_limits<int>::min());
    LOGD("float 所占字节数:%lu, 最大值:%f, 最小值：%f", sizeof(float), numeric_limits<float>::max(),
         numeric_limits<float>::min());
    LOGD("long 所占字节数:%lu, 最大值:%ld, 最小值：%ld", sizeof(long), numeric_limits<long>::max(),
         numeric_limits<long>::min());
}

void TypeTest::typeCast() {
    string str1 = Util::byteToHex('a');
    LOGD("byteToHex: %s", str1.c_str());

    string str2 = "123abc"; //0x313233616263
    str2 = Util::bytesToHex(const_cast<char *>(str2.c_str()), str2.length());
    LOGD("bytesToHex: %s", str2.c_str());

    string str3 = "313233616263";
    str3 = Util::hexToBytes(const_cast<char *>(str3.c_str()), str3.length());
    LOGD("hexToBytes: %s", str3.c_str());

    string str4 = "55ed4f1c-7cf4-3315-3a9d-4ac8254ff18b";
    str4 = Util::removeChar(str4, '-');
    LOGD("removeChar: %s", str4.c_str());
}

