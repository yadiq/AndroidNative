#include <string>
#include <jni.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//打印日志 LOGI("failed to open file: %s %d", "string", 0);
#define  LOG_TAG    "JNI_log"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//extern "C" 告诉 C++ 编译器以 C 的方式来编译这个函数，以方便其他 C 程序链接和访问该函数

//字符串操作
//jstring是指向JVM内部的一个字符串，不能直接使用，需转为char*后才能使用
//Java中默认是使用Unicode编码，C/C++默认使用UTF编码，需要进行编码转换
//GetStringLength/GetStringUTFLength 获取Unicode/UTF-8字符串的长度

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_org_freedesktop_test_Test_operateString2(JNIEnv *env, jobject thiz, jstring str) {
    //从java的内存中把字符串拷贝出来  在native使用
    const char *strFromJava = (char *) env->GetStringUTFChars(str, NULL);
    if (strFromJava == NULL) {
        //必须空检查
        return NULL;
    }

    //将strFromJava拷贝到buff中,待会儿好拿去生成字符串
    char buff[128] = {0};
    strcpy(buff, strFromJava);
    strcat(buff, " 在字符串后面加点东西");

    //申请空间后需要手动释放，Get和Release一一对应
    env->ReleaseStringUTFChars(str, strFromJava);

    //UTF编码自动转为Unicode编码
    return env->NewStringUTF(buff);
}

//数组操作
JNIEXPORT jint JNICALL
Java_org_freedesktop_test_Test_sumArray2(JNIEnv *env, jobject thiz, jintArray array) {
    //数组求和
    int result = 0;

    //此种方式比较危险,GetIntArrayElements会直接获取数组元素指针,是可以直接对该数组元素进行修改的.
    jint *c_arr = env->GetIntArrayElements(array, NULL);
    if (c_arr == NULL) {
        return 0;
    }
    //c_arr[0] = 15;
    jint len = env->GetArrayLength(array);
    for (int i = 0; i < len; ++i) {
        //result += *(c_arr + i); 写成这种形式,或者下面一行那种都行
        result += c_arr[i];
    }
    //有Get,一般就有Release
    env->ReleaseIntArrayElements(array, c_arr, 0);

    return result;
}

#ifdef __cplusplus
}
#endif