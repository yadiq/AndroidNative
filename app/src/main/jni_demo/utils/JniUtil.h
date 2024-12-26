//
// Created by guoya on 2024/8/8.
//

#ifndef ANDROIDNATIVE_JNIUTIL_H
#define ANDROIDNATIVE_JNIUTIL_H


class JniUtil {

};

JNIEnv *getEnv(JavaVM *jvm);
void releaseEnv(JavaVM *jvm);

#endif //ANDROIDNATIVE_JNIUTIL_H
