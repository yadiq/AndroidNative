#ifndef BWL_SIGN_UTIL_H
#define BWL_SIGN_UTIL_H

#include <jni.h>
#include "JniUtil.h"

string getSign(JNIEnv *env);//获取应用签名
string getPackageName(JNIEnv *env);//获取应用包名
int getFlags(JNIEnv *env);//获取系统信息flags

#endif //BWL_SIGN_UTIL_H