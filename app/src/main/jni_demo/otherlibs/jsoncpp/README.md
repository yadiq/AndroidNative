##jsoncpp用法

```
    //string 转 json
    string str = "{\"key1\":\"value1\",\"key2\":\"value2\"}";//json格式的字符串
    Json::Value json;//json键值对
    Json::Reader reader;//解释器
    if (reader.parse(str, json)) {
        LOGD("解析成功");
        Json::Value::Members mem = json.getMemberNames();
        for (auto iter = mem.begin(); iter != mem.end(); iter++) {
            string key = *iter;
            string value = json[key].asString();
            LOGD("%s:%s", key.c_str(), value.c_str());
        }
    } else {
        LOGD("解析失败");
    }

    //json 转 string
    Json::Value json;//json键值对
    json["key1"] = "value1";
    json["key2"] = "value2";
    string str3 = json.toStyledString();//转化器-json美化
    LOGD("json美化1, %s", str3.c_str());
    Json::StyledWriter swriter;//转化器-json美化
    string str2 = swriter.write(json);
    LOGD("json美化2, %s", str2.c_str());
    Json::FastWriter fwriter;//转化器-json压缩
    string str1 = fwriter.write(json);
    LOGD("json压缩, %s", str1.c_str());
```