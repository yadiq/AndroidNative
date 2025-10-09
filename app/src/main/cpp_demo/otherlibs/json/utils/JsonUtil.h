//
// Created by gyd on 2025/10/9.
//

#ifndef ANDROIDNATIVE_JSONUTIL_H
#define ANDROIDNATIVE_JSONUTIL_H

#include <string>

class JsonUtil {
    /**
     * 预处理 JSON5 → JSON
     * @param input
     * @return
     */
    static std::string json5ToJson(std::string& input);
};


#endif //ANDROIDNATIVE_JSONUTIL_H
