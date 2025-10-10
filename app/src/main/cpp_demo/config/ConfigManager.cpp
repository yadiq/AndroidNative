//
// Created by Adi on 2025/10/8.
//
#include <fstream>
#include <sstream>

#include "ConfigManager.h"

/**
 * 读写config文件
 * @return
 */

ConfigManager &ConfigManager::getInstance() {
    // C++11 以后，局部静态变量初始化是线程安全的
    // 第一次调用 getInstance() 时才创建实例
    static ConfigManager instance;
    return instance;
}

ConfigManager::ConfigManager() = default;

ConfigManager::~ConfigManager() = default;

void ConfigManager::init(std::string &storageDir) {
    path = storageDir + "/config.json5";
    //读文件
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::runtime_error("无法打开文件: " + path);
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string json5Str = buffer.str();
    //转为json
    mJson = JsonUtil::json5StrToJson(json5Str);
}

std::string ConfigManager::getValue(const std::string &key) {
    std::string result;
    if (mJson.contains(key)) {
        result = mJson[key];
    }
    return result;
}

void ConfigManager::setValue(const std::string &key, const std::string &value) {
    mJson[key] = value;
    //转为string
    std::string jsonStr = JsonUtil::jsonToStr(mJson);
    //写文件
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        throw std::runtime_error("无法写入文件: " + path);
    }
    ofs << jsonStr;
}




