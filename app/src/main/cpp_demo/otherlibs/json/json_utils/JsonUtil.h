//
// Created by gyd on 2025/10/9.
//

#ifndef ANDROIDNATIVE_JSONUTIL_H
#define ANDROIDNATIVE_JSONUTIL_H

#include <string>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JsonUtil {
public:

    /**
     * string 转 JSON
     * @param input
     * @return
     */
    static json jsonStrToJson(std::string &jsonStr);
    static json json5StrToJson(std::string &json5Str);
    /**
     * JSON 转 string
     * @param j
     * @return
     */
    static std::string jsonToStr(json &j);

private:
    /**
     * 预处理 JSON5字符串 → JSON字符串
     * @param input
     * @return
     */
    static std::string json5ToJson(std::string &input);

};


#endif //ANDROIDNATIVE_JSONUTIL_H
