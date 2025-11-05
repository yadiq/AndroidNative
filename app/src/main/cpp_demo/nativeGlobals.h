//
// Created by gyd on 2025/11/5.
//

#ifndef ANDROIDNATIVE_NATIVEGLOBALS_H
#define ANDROIDNATIVE_NATIVEGLOBALS_H

#include <jni.h>
#include <bits/pthread_types.h>

//存储全局变量
//extern 变量声明，不分配内存，告诉编译器变量在其他地方定义。可跨文件访问

//java侧的字段id
extern jfieldID nativeDataFieldId; //存储native指针
extern jmethodID nativeSetMessageFieldId; //回调函数

extern JavaVM *javaVM; //JVM虚拟机实例
extern pthread_key_t threadKey; //存储线程本地数据的key
//extern jobject app; //类实例，用来访问它的变量

#endif //ANDROIDNATIVE_NATIVEGLOBALS_H
