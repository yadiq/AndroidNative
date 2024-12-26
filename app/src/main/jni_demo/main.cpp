#include <jni.h>
#include <string>

#include "cpp_test/Test1.h"
#include "utils/Util.h"

extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_test_Test_test1(JNIEnv *env, jclass /* this */) {

    //类对象
    /*Test1 test1;//声明对象
    test1.setValue(123);
    int result1 = test1.getValue();*/
    //Test1::pintDataTypeSize();
    //char *bytes = "abc123";
    //std::string hexStr = Util::bytesToHex(bytes, strlen(bytes));
    Test1::curlGet();
    Test1::curlPost();
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