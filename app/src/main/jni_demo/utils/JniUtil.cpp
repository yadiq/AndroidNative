//
// Created by guoya on 2024/8/8.
//

#include <jni.h>

#include "JniUtil.h"

//获取JNI环境
//附加当前线程到虚拟机VM当中，向虚拟机分配线程独立的env，之后GetEnv返回的env才有值
JNIEnv *getEnv(JavaVM *jvm) {
    JNIEnv *env = NULL;
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (status != JNI_OK) {
        status = jvm->AttachCurrentThread(&env, NULL);
        if(status != JNI_OK){
            return NULL;
        }
    }
    return env;
}

//释放JNI环境
void releaseEnv(JavaVM *jvm) {
    JNIEnv *env;
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (status == JNI_OK) {
        jvm->DetachCurrentThread();
    }
}
