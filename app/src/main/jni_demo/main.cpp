#include <jni.h>
#include <string>

#include "utils/Util.h"
#include "utils/CurlHttp.h"
#include "utils_android/JniUtil.h"
#include "utils_android/LogUtil.h"
#include "otherlibs/jsoncpp/JsonUtil.h"

//JNIEnv* 指向JNI环境的指针，可以通过它来访问JNI提供的接口方法:
//jobject Java对象中的this
//jclass Java对象中的this,静态方法中使用

//基本数据类型，不需要进行转换，可以直接在 JNI 中使用：
//Java类型 Native类型 c类型           有无符合 字长
//boolean jboolean   unsigned char   uint8_t
//byte	  jbyte	     signed char     int8_t
//char	  jchar	     unsigned short  uint16_t
//short	  jshort	 signed short    int16_t
//int	  jint	     int             int32_t
//long	  jlong	     long            int64_t
//float	  jfloat	 float           int32_t
//double  jdouble	 double          int64_t
//注：java中char占两个字节，c中char占一个字节

//非基本数据类型称为引用类型：
//string  jstring    char*
//int[]   jintArray  int*
//byte[]  jbyteArray char*

//jstring是指向JVM内部的一个字符串，不能直接使用，需转为char*后才能使用
//Java中默认是使用UTF-16编码，C/C++默认使用UTF-8编码，需要进行编码转换
//GetStringLength/GetStringUTFLength 获取UTF-16/UTF-8字符串的长度
//NewString/NewStringUTF 构建UTF-16/UTF-8字符串对象

//extern "C" 告诉 C++ 编译器以 C 的方式来编译这个函数，以方便其他 C 程序链接和访问该函数

//网络请求
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_httpget(JNIEnv *env, jclass thiz, jstring jstr) {
    string url = JniUtil::jstringToString(env, jstr);
    //网络请求
    string response;
    CurlHttp curl;
    auto result = curl.getRequest(url, response);
    if (result == 200) {
        //json解析
        Json::Value responseJson;
        bool responseReader = JsonUtil::stringToJson(response, responseJson);
        if (responseReader) {
            string origin = responseJson["origin"].asString();
            LOGD("httpget请求成功. origin:%s", origin.c_str());
        } else {
            LOGD("httpget请求失败. json解析失败");
        }
    } else {
        LOGD("httpget请求失败. code: %d,response: %s", result, response.c_str());
    }
    return env->NewStringUTF(response.c_str());
}

//加解密
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_encrypt(JNIEnv *env, jclass thiz, jstring jstr) {
//    TypeTest::typeCast();


    std::string hexStr = "Hello from C++";
    return env->NewStringUTF(hexStr.c_str());
}

//数据类型转换
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_type(JNIEnv *env, jclass thiz, jstring jstr) {
//    TypeTest::typeCast();


    std::string hexStr = "Hello from C++";
    return env->NewStringUTF(hexStr.c_str());
}

//测试
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_test1(JNIEnv *env, jclass thiz, jstring jstr) {
//    TypeTest::typeCast();


    std::string hexStr = "Hello from C++";
    return env->NewStringUTF(hexStr.c_str());
}