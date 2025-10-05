//
// Created by Adi on 2024/12/27.
// 测试网络

#include "CurlTest.h"
#include "../utils/CurlHttp.h"
#include "../utils_android/LogUtil.h"
#include "../otherlibs/jsoncpp/JsonUtil.h"

//注意:
// 需提前设置libcurl需要的程序环境
// CurlHttp::init();
// CurlHttp::cleanup();

void CurlTest::curlGet() {
    //get请求
    string urlStr = "http://httpbin.org/get?param1=value1";
    string responseStr;
    CurlHttp curl;
    auto res = curl.getRequest(urlStr, responseStr);
    if (res == 200) {
        LOGD("curlGet success.\n%s", responseStr.c_str());
        //json解析
        Json::Value responseJson;
        bool responseReader = JsonUtil::stringToJson(responseStr, responseJson);
        if (responseReader) {
            string origin = responseJson["origin"].asString();
            LOGD("json解析成功. origin: %s", origin.c_str());
        } else {
            LOGD("json解析失败");
        }
    } else {
        LOGE("curlGet error. code: %ld, response: %s", res, responseStr.c_str());
    }
}

void CurlTest::curlPost() {
    //post请求
    string urlStr = "http://httpbin.org/post";
    Json::Value json;//键值对
    json["key1"] = "value1";
    json["key2"] = "value2";
    string bodyStr = JsonUtil::jsonToString(json);
    string responseStr;
    CurlHttp curl;
    auto res = curl.postRequest(urlStr, bodyStr, responseStr);
    if (res == 200) {
        LOGD("curlPost success.\n%s", responseStr.c_str());
        //json解析
        Json::Value responseJson;
        bool responseReader = JsonUtil::stringToJson(responseStr, responseJson);
        if (responseReader) {
            string origin = responseJson["origin"].asString();
            LOGD("json解析成功. origin: %s", origin.c_str());
        } else {
            LOGD("json解析失败");
        }
    } else {
        LOGE("curlPost error. code: %ld, response: %s", res, responseStr.c_str());
    }
}