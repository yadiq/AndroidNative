//
// Created by Adi on 2025/10/8.
//

#include "ConfigManager.h"

// ------------------------
// 单例实例获取
// C++11 以后，局部静态变量初始化是线程安全的。
// 第一次调用 getInstance() 时才创建实例。
// ------------------------
ConfigManager& ConfigManager::getInstance() {

    static ConfigManager instance;
    return instance;
}

// ------------------------
// 构造函数 / 析构函数
// ------------------------
ConfigManager::ConfigManager() = default;
ConfigManager::~ConfigManager() = default;

// ------------------------
// 设置配置
// ------------------------
void ConfigManager::setValue(const std::string& key, const std::string& value) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    config_[key] = value;
}

// ------------------------
// 获取配置
// ------------------------
std::string ConfigManager::getValue(const std::string& key) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    auto it = config_.find(key);
//    return (it != config_.end()) ? it->second : "";
    return ""
}