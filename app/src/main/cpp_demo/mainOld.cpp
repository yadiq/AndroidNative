#include <jni.h>
#include <string>
#include "utils_android/JniUtil.h"

//测试
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_test(JNIEnv *env, jclass thiz, jstring jstr) {
    string str = JniUtil::jstringToString(env, jstr);
    return env->NewStringUTF(str.c_str());
}

//当动态库被加载时系统会调用
//JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
//    gJvm = vm; //保存全局变量
//    return JNI_VERSION_1_6;
//}