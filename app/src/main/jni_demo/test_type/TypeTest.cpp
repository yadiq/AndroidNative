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
}

void TypeTest::typeCast() {
    const char *cstr = "123abc";//49 50 51 97 98 99
    string hex = Util::cstringToHex(const_cast<char *>(cstr), strlen(cstr));
    LOGD("%s => %s", cstr, hex.c_str());

}

