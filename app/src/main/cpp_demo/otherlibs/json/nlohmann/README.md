## nlohmann::json 用法

```
    //创建 JSON 对象
    json j;
    j["name"] = "Alice";
    j["age"] = 25;
    j["is_student"] = false;
    j["skills"] = {"C++", "Python", "Qt"};

    //JSON 转 string
    string str = j.dump(); //dump(4) 表示缩进 4 个空格
    LOGD("str1 %s", str.c_str());

    //访问字段
    //j["name"]
    //j["skills"][0]
    //修改字段
    //j["age"] = 26;
    //检查字段是否存在
    //if (j.contains("age"))
    //删除字段
    //j.erase("is_student");

    //从字符串解析 JSON
    json j2 = json::parse(str);
    string str2 = j2.dump(4);
    LOGD("str1 %s", str2.c_str());
    
//R"( ... )" 是 C++ 原始字符串，避免手动转义引号
//    std::string jsonStr = R"({
//        "name": "yadi",
//        "age": 25,
//        "languages": ["C++", "Kotlin", "Python"]
//    })";
```