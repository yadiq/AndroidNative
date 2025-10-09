//
// Created by Adi on 2025/10/8.
//

#include "ConfigManager.h"

/**
 * 获取单例时，读文件到json （一个文件对应一个单例，一个函数对应一个层级的key）
 * 读key时，读json
 * 写key时，写json 写文件
 *
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

void ConfigManager::setValue(const std::string &key, const std::string &value) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    config_[key] = value;
}

std::string ConfigManager::getValue(const std::string &key) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    auto it = config_.find(key);
//    return (it != config_.end()) ? it->second : "";
    return ""
}