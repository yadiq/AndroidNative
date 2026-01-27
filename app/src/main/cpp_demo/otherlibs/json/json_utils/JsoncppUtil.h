//
// Created by gyd on 2026/1/27.
//

#ifndef ANDROIDNATIVE_JSONCPPUTIL_H
#define ANDROIDNATIVE_JSONCPPUTIL_H


#include "jsoncpp/json/value.h"

class JsoncppUtil {
public:
    /**
     * Json::Value 转 string
     * @param json
     * @return string
     */
    static std::string jsonToString(Json::Value& json);
    /**
     * string 转 Json::Value
     * @param value
     * @param json
     * @return 成功失败
     */
    static bool stringToJson(std::string& value, Json::Value& json);
    /**
     * cstring 转 Json::Value
     * @param value
     * @param json
     * @return 成功失败
     */
    static bool stringToJson(char* value, Json::Value& json);
};


#endif //ANDROIDNATIVE_JSONCPPUTIL_H
