//
// Created by guoya on 2024/8/8.
//

#include "JniUtil.h"

//附加当前线程到虚拟机VM当中，向虚拟机分配线程独立的env，之后GetEnv返回的env才有值
JNIEnv *JniUtil::getEnv(JavaVM *jvm) {
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

void JniUtil::releaseEnv(JavaVM *jvm) {
    JNIEnv *env;
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (status == JNI_OK) {
        jvm->DetachCurrentThread();
    }
}

string JniUtil::jstringToString(JNIEnv *env, jstring jstr) {
    const char *str = (char *) env->GetStringUTFChars(jstr, NULL);
    string cstr = str;
    env->ReleaseStringUTFChars(jstr, str);
    return cstr;
}

jstring JniUtil::stringToJstring(JNIEnv *env, string str) {
    jstring jstr = env->NewStringUTF(str.c_str());
    return jstr;
}

string JniUtil::jbyteArrayToString(JNIEnv *env, jbyteArray byteArray) {
    jbyte *byte = env->GetByteArrayElements(byteArray, 0);
    char *cstr = reinterpret_cast<char *>(byte);
    int len = env->GetArrayLength(byteArray);
    string str(cstr, len);
    return str;
}

jbyteArray JniUtil::stringToJbyteArray(JNIEnv *env, string str) {
    jbyte *byte = (jbyte *) str.c_str();
    int length = str.length();
    jbyteArray byteArray = env->NewByteArray(length);
    env->SetByteArrayRegion(byteArray, 0, length, byte);
    return byteArray;
}
