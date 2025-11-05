//
// Created by guoya on 2024/8/8.
//

#ifndef ANDROIDNATIVE_JNIUTIL_H
#define ANDROIDNATIVE_JNIUTIL_H

#include <jni.h>
#include <string>

using namespace std;

class JniUtil {
public:
    /**
     * 获取当前线程的JNI环境
     * @param jvm
     * @param threadKey
     * @return
     */
    static JNIEnv *getJNIEnv(JavaVM *javaVM, pthread_key_t threadKey);

    /**
     * jstring 转 string
     * @param env
     * @param jstr
     * @return
     */
    static string jstringToString(JNIEnv *env, jstring jstr);

    /**
     * string 转 jstring
     * @param env
     * @param cstr
     * @return
     */
    static jstring stringToJstring(JNIEnv *env, string str);
    /**
     * jbyteArray 转 string
     * @param env
     * @param jstr
     * @return
 */
    static string jbyteArrayToString(JNIEnv *env, jbyteArray byteArray);

    /**
     * std::string 转 jbyteArray
     * @param env
     * @param cstr
     * @return
     */
    static jbyteArray stringToJbyteArray(JNIEnv *env, string str);
};



#endif //ANDROIDNATIVE_JNIUTIL_H
