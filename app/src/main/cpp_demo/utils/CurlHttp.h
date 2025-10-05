//
// Created by guoya on 2024/12/24.
//

#ifndef ANDROIDNATIVE_CURLHTTP_H
#define ANDROIDNATIVE_CURLHTTP_H


#include "curl/curl.h"
#include <string>
using namespace std;

class CurlHttp {
public:
    CurlHttp();
    virtual ~CurlHttp();
    /**
     * 全局初始化
     */
    static void init();
    /**
     * 全局释放资源
     */
    static void cleanup();

public:
    /**
     * 发送get请求
     * @return HTTP状态码,200成功
     */
    long getRequest(const string &url, string &response);
    /**
     * 发送post请求
     * @return HTTP状态码,200成功
     */
    long postRequest(const string &url, const string &postParams, string &response);
private:
    CURL* curl;
};

#endif //ANDROIDNATIVE_CURLHTTP_H


