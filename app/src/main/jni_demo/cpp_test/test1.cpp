//
// Created by guoya on 2024/12/19.
//
#include <limits>

#include "Test1.h"
#include "../utils/Util.h"
#include "../utils/CurlHttp.h"
#include "../otherlibs/jsoncpp/json/json.h"

using namespace std;

/*Test1::Test1(int i) {
    value = i;
    LOGD("构造函数 i=%d", i);
}

Test1::~Test1() {
    value = 0;
    LOGD("析构函数");
}

void Test1::setValue(int i) {
    value = i;
    return false;
}

int Test1::getValue() {
    return value;
}*/


void Test1::pintDataTypeSize() {
    LOGD("bool 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(bool), numeric_limits<bool>::max(),
         numeric_limits<bool>::min());
    LOGD("char 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(char), numeric_limits<char>::max(),
         numeric_limits<char>::min());
    LOGD("int 所占字节数:%lu, 最大值:%d, 最小值：%d", sizeof(int), numeric_limits<int>::max(),
         numeric_limits<int>::min());
    LOGD("float 所占字节数:%lu, 最大值:%f, 最小值：%f", sizeof(float), numeric_limits<float>::max(),
         numeric_limits<float>::min());
}

//测试网络
void Test1::curlGet() {
    CurlHttp::init();

    //get请求
    string urlStr = "http://httpbin.org/get?param1=value1";
    string responseStr;
    CurlHttp curl;
    auto res = curl.getRequest(urlStr, responseStr);
    if (res == 200)
        LOGD("curlGet success.\n%s", responseStr.c_str());
    else
        LOGE("curlGet error. code: %ld", res);


    CurlHttp::cleanup();
}

void Test1::curlPost() {
    CurlHttp::init();

    //post请求
    string urlStr = "http://httpbin.org/post";
    Json::Value json;//键值对
    json["key1"] = "value1";
    json["key2"] = "value2";
    string postParams = json.toStyledString();
    //string postParams = "key1=value1&key2=value2";
    string responseStr;
    CurlHttp curl;
    auto res = curl.postRequest(urlStr, postParams, responseStr);
    if (res == 200) {
        LOGD("curlPost success.\n%s", responseStr.c_str());
    } else {
        LOGE("curlPost error. code: %ld", res);
    }
    CurlHttp::cleanup();
}
