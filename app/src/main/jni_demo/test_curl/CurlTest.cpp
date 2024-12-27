//
// Created by Adi on 2024/12/27.
//

#include "CurlTest.h"
#include "../utils/CurlHttp.h"
#include "../utils_android/LogUtil.h"
#include "../otherlibs/jsoncpp/json/value.h"


//测试网络
void CurlTest::curlGet() {
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

void CurlTest::curlPost() {
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