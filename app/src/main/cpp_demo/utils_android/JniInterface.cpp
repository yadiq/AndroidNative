//
// Created by gyd on 2025/10/27.
//

#include "JniInterface.h"
#include "../utils_android/JniUtil.h"

//extern 声明在其他文件中定义的全局变量，可以在多个文件之间共享
extern JavaVM *gJvm; //用于获取环境变量env
extern jobject gCallback; //用于获取callback

void JniInterface::onInputEvent(int type) {
    if (gJvm == nullptr || gCallback == nullptr)
        return;
    //获取env
    JNIEnv *env = JniUtil::getEnv(gJvm);
    //获取 回调类与方法ID
    jclass cls = env->GetObjectClass(gCallback);
    jmethodID mid = env->GetMethodID(cls, "onInputEvent", "(I)V");
    //调用 Java回调
    env->CallVoidMethod(gCallback, mid, type);
    //释放env
    JniUtil::releaseEnv(gJvm);
}
