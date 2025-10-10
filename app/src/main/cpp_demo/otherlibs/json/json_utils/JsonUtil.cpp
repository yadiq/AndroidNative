//
// Created by gyd on 2025/10/9.
//
#include <regex>

#include "JsonUtil.h"

json JsonUtil::jsonStrToJson(std::string &jsonStr) {
    //json j = json::parse(jsonStr); //从字符串解析JSON
    //return j;
    try {
        return json::parse(jsonStr);
    } catch (const std::exception &e) {
        throw std::runtime_error(std::string("解析 JSON 失败: ") + e.what());
    }
}

json JsonUtil::json5StrToJson(std::string &json5Str) {
    std::string jsonStr = json5ToJson(json5Str);
    json j = jsonStrToJson(jsonStr);
    return j;
}

std::string JsonUtil::jsonToStr(json &j) {
    std::string jsonStr = j.dump(2); //缩进2个空格
    return jsonStr;
}


std::string JsonUtil::json5ToJson(std::string &input) {
    std::string out = input;
    // 去除单行注释 //
    out = std::regex_replace(out, std::regex(R"(//[^\n]*)"), "");
    // 去除多行注释 /* ... */
    //out = std::regex_replace(out, std::regex(R"(/\*.*?\*/)", std::regex::dotall), "");
    out = std::regex_replace(out, std::regex(R"(/\*[\s\S]*?\*/)"), "");
    // 去除尾随逗号
    out = std::regex_replace(out, std::regex(R"(,\s*([\]}]))"), "$1");
    // 单引号替换为双引号
    out = std::regex_replace(out, std::regex(R"(')"), "\"");
    return out;
}






