//
// Created by Adi on 2024/12/30.
// 动态注册

#include <jni.h>
#include "utils_android/JniUtil.h"
#include "utils/Util.h"

JNIEXPORT jstring JNICALL
registerNatives(JNIEnv *env, jclass thiz, jstring jstr) {
    string str = JniUtil::jstringToString(env, jstr);
    string hex = Util::bytesToHex(const_cast<char *>(str.c_str()), str.length());
    jstring resultStr = env->NewStringUTF(hex.c_str());
    return resultStr;
}

//构建 JNINativeMethod 数组
static JNINativeMethod methods[] = {
        {"registerNatives", "(Ljava/lang/String;)Ljava/lang/String;", (void *) registerNatives},
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