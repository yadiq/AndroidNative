//
// Created by Adi on 2025/10/8.
//

#ifndef ANDROIDNATIVE_CONFIGMANAGER_H
#define ANDROIDNATIVE_CONFIGMANAGER_H

#include <string>
#include "json_utils/JsonUtil.h"


class ConfigManager {
public:
    //获取单例实例
    static ConfigManager& getInstance();

    //读文件，转为json，缓存起来
    void init(std::string& storageDir);

    //获取配置
    std::string getValue(const std::string& key);

    //设置配置
    void setValue(const std::string& key, const std::string& value);

private:
    // 私有构造函数和析构函数
    ConfigManager();
    ~ConfigManager();

    json mJson; //JSON对象
    std::string path; //文件路径

    // 禁止拷贝/赋值：保证全局只有一个实例。
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

//    std::map<std::string, std::string> config_;
//    std::mutex mutex_;
};


#endif //ANDROIDNATIVE_CONFIGMANAGER_H
