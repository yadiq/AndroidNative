//
// Created by Adi on 2025/10/8.
//

#ifndef ANDROIDNATIVE_CONFIGMANAGER_H
#define ANDROIDNATIVE_CONFIGMANAGER_H

#include <string>

//using namespace std;

class ConfigManager {
public:
    // 获取单例实例
    static ConfigManager& getInstance();

    // 设置配置
    void setValue(const std::string& key, const std::string& value);

    // 获取配置
    std::string getValue(const std::string& key);

private:
    // 私有构造函数和析构函数
    ConfigManager();
    ~ConfigManager();

//    static bool readJsonFile(const std::string& path, json& outJson) {


    // 禁止拷贝/赋值：保证全局只有一个实例。
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

//    std::map<std::string, std::string> config_;
//    std::mutex mutex_;
};


#endif //ANDROIDNATIVE_CONFIGMANAGER_H
