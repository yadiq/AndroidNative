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
    const char *cstr1 = "123abc";//49 50 51 97 98 99
    string hex1 = Util::cstringToHex(const_cast<char *>(cstr1), strlen(cstr1));
    LOGD("cstringToHex: %s => %s", cstr1, hex1.c_str());

    string str1 = "55ed4f1c-7cf4-3315-3a9d-4ac8254ff18b";
    string str2 = Util::removeChar(str1, '-');
    LOGD("removeChar: %s", str2.c_str());

//    std::string str2 = "Text with some   spaces";
//    str2.erase(std::remove(str2.begin(), str2.end(), ' '),
//               str2.end());
//    LOGD("removeChar: %s", str2.c_str());
}

