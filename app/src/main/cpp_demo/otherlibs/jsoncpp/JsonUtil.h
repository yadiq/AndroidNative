//
// Created by guoya on 2024/12/27.
//

#ifndef FLYINGCARNATIVE_JSONUTIL_H
#define FLYINGCARNATIVE_JSONUTIL_H

#include <string>
#include "json/json.h"
using namespace std;

class JsonUtil {
public:
    /**
     * Json::Value 转 string
     * @param json
     * @return string
     */
    static string jsonToString(Json::Value& json);
    /**
     * string 转 Json::Value
     * @param value
     * @param json
     * @return 成功失败
     */
    static bool stringToJson(string& value, Json::Value& json);
    /**
     * cstring 转 Json::Value
     * @param value
     * @param json
     * @return 成功失败
     */
    static bool stringToJson(char* value, Json::Value& json);
};


#endif //FLYINGCARNATIVE_JSONUTIL_H
