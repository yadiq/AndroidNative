#include <jni.h>
#include <string>

#include "utils/Util.h"
#include "test_type/TypeTest.h"

//测试网络
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_test_Test_test1(JNIEnv *env, jclass /* this */) {
    TypeTest::typeCast();


    std::string hexStr = "Hello from C++";
    return env->NewStringUTF(hexStr.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_test_Test_test2(JNIEnv *env, jclass /* this */, jstring str) {
    //从java的内存中把字符串拷贝出来
    const char *strFromJava = (char *) env->GetStringUTFChars(str, NULL);

    std::string hello = "Hello from C++";
    hello.append(strFromJava);

    //申请空间后需要手动释放
    env->ReleaseStringUTFChars(str, strFromJava);
    //UTF编码自动转为Unicode编码
    jstring result = env->NewStringUTF(hello.c_str());
    return result;
}