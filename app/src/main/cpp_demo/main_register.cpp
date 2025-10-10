//
// Created by Adi on 2024/12/30.
// 动态注册

#include <jni.h>
#include <fstream>

#include "utils_android/JniUtil.h"
#include "utils/Util.h"
#include "utils_android/LogUtil.h"
#include "config/ConfigManager.h"




string storage_dir; //存储路径

//JNIEXPORT jstring JNICALL
//registerNatives(JNIEnv *env, jclass thiz, jstring jstr) {
//    string str = JniUtil::jstringToString(env, jstr);
//    string hex = Util::bytesToHex(const_cast<char *>(str.c_str()), str.length());
//    jstring resultStr = env->NewStringUTF(hex.c_str());
//    return resultStr;
//}

//设置参数
JNIEXPORT void JNICALL
set_param(JNIEnv *env, jclass thiz, jstring storage_dir_) {
    storage_dir = JniUtil::jstringToString(env,storage_dir_);
}

//开始运行
JNIEXPORT void JNICALL
start(JNIEnv *env, jclass thiz) {
    //读取配置文件
    ConfigManager::getInstance().init(storage_dir);
    ConfigManager::getInstance().setValue("name", "小王");
    string name = ConfigManager::getInstance().getValue("name");
    LOGD("读取name, %s", name.c_str());


}

//构建 JNINativeMethod 数组
static JNINativeMethod methods[] = {
//        {"registerNatives", "(Ljava/lang/String;)Ljava/lang/String;", (void *) registerNatives},
        {"set_param", "(Ljava/lang/String;)V", (void *) set_param},
        {"start", "()V", (void *) start},
};

//动态注册的入口函数
jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    //获取JNI env变量
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    //获取native方法所在类
    jclass clazz = env->FindClass("org/freedesktop/demo/Demo");
    if (clazz == NULL) {
        return -1;
    }
    // 动态注册native方法
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return -1;
    }
    return JNI_VERSION_1_4;
}