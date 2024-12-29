//
// Created by guoya on 2024/12/24.
//

#include "CurlHttp.h"
#include "Util.h"
#include "../utils_android/LogUtil.h"

CurlHttp::CurlHttp() {
    //初始化
    curl = curl_easy_init();

    // 接收响应头数据，0代表不接收 1代表接收
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    //设置不使用任何信号/警报处理程序。在多线程场景下设置
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    //设置超时时间，单位秒
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    //不验证HTTPS证书的合法性
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    //不验证https请求时返回的证书是否与请求的域名相符合，避免被中间者篡改证书文件
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    //CURLOPT_VERBOSE的值为1时，会显示详细的调试信息
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
}

CurlHttp::~CurlHttp() {
    curl_easy_cleanup(curl);
    curl = nullptr;
}

void CurlHttp::init() {
    //设置libcurl需要的程序环境。在程序调用libcurl中的任何其他函数之前，必须在程序中至少调用此函数一次
    curl_global_init(CURL_GLOBAL_ALL);
}

void CurlHttp::cleanup() {
    curl_global_cleanup();
}

//回调函数
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    ((string *) userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

long CurlHttp::getRequest(const string &url, string &response) {
    //HTTP状态码
    long http_code = -1;
    if (curl == nullptr)
        return http_code;
    /////////////////通用请求////////////////
    //设置请求的URL地址
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //设置数据接收函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //进行网络操作
    CURLcode res = curl_easy_perform(curl);
    /////////////////数据响应////////////////
    //查询HTTP状态码
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    //失败时返回错误信息
    if (res != CURLE_OK) {
        response.append(curl_easy_strerror(res));
    }
    //LOGD("GET %ld %s\n%s", http_code, url.c_str(), response.c_str());
    return http_code;
}

long CurlHttp::postRequest(const string &url, const string &postParams, string &response) {
    //HTTP状态码
    long http_code = -1;
    if (curl == nullptr)
        return http_code;
    /////////////////post请求相关////////////////
    //设置请求头
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type:application/json");
    //headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    //设置请求为post请求
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    //设置post请求的参数
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());
    /////////////////通用请求////////////////
    //设置请求的URL地址
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //设置数据接收函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //进行网络操作
    CURLcode res = curl_easy_perform(curl);
    /////////////////数据响应////////////////
    //查询HTTP状态码
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    //失败时返回错误信息
    if (res != CURLE_OK) {
        response.append(curl_easy_strerror(res));
    }
    //LOGD("POST %ld %s\n%s", http_code, url.c_str(), response.c_str());
    return http_code;
}




