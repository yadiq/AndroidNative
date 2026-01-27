//
// Created by gyd on 2026/1/27.
//

#include "JsoncppUtil.h"
#include "jsoncpp/json/reader.h"
#include "jsoncpp/json/writer.h"

std::string JsoncppUtil::jsonToString(Json::Value& json) {
    Json::FastWriter fwriter;//转化器-json压缩
    std::string str = fwriter.write(json);
    /*string str3 = json.toStyledString();//转化器-json美化1
    LOGD("json美化1, %s", str3.c_str());
    Json::StyledWriter swriter;//转化器-json美化2
    string str2 = swriter.write(json);
    LOGD("json美化2, %s", str2.c_str());*/
    return str;
}

bool JsoncppUtil::stringToJson(std::string& value, Json::Value& json) {
    bool result = false;
    Json::Reader reader;//解释器
    if (reader.parse(value, json)) {
        result = true;
        /*LOGD("json解析成功");
        Json::Value::Members mem = json.getMemberNames();
        for (auto iter = mem.begin(); iter != mem.end(); iter++) {
            string itemKey = *iter;
            if (json[itemKey].type() == Json::stringValue) {
                string itemValue = json[itemKey].asString();
                LOGD("%s:%s", itemKey.c_str(), itemValue.c_str());
            }
        }*/
    } else {
        //LOGD("json解析失败");
    }
    return result;
}

bool JsoncppUtil::stringToJson(char *value, Json::Value &json) {
    bool result = false;
    Json::Reader reader;//解释器
    if (reader.parse(value, json)) {
        result = true;
        //LOGD("json解析成功");
    } else {
        //LOGD("json解析失败");
    }
    return result;
}