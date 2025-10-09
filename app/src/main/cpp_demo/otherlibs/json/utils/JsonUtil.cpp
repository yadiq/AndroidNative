//
// Created by gyd on 2025/10/9.
//
#include <regex>

#include "JsonUtil.h"

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