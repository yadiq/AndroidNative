#include <string.h>
#include <jni.h>
#include <android/log.h>

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

//打印日志 LOGI("failed to open file: %s %d", "string", 0);
#define  LOG_TAG    "JNI_log"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//动态注册

JNIEXPORT jstring JNICALL
operateString3(JNIEnv *env, jobject thiz, jstring str) {
    //从java的内存中把字符串拷贝出来  在native使用
    const char *strFromJava = (char *) (*env)->GetStringUTFChars(env, str, NULL);
    if (strFromJava == NULL) {
        //必须空检查
        return NULL;
    }

    //将strFromJava拷贝到buff中,待会儿好拿去生成字符串
    char buff[128] = {0};
    strcpy(buff, strFromJava);
    strcat(buff, " 在字符串后面加点东西");

    //申请空间后需要手动释放，Get和Release一一对应
    (*env)->ReleaseStringUTFChars(env, str, strFromJava);

    //UTF编码自动转为Unicode编码
    return (*env)->NewStringUTF(env, buff);
}

//数组操作
JNIEXPORT jint JNICALL
sumArray3(JNIEnv *env, jobject thiz, jintArray array) {
    //数组求和
    int result = 0;

    //类型转换 jintArray -> jint*
    jint *c_arr = (*env)->GetIntArrayElements(env, array, NULL);
    if (c_arr == NULL) {
        return 0;
    }
    //c_arr[0] = 15;
    jint len = (*env)->GetArrayLength(env, array);
    for (int i = 0; i < len; ++i) {
        //result += *(c_arr + i); 写成这种形式,或者下面一行那种都行
        result += c_arr[i];
    }
    //有Get,一般就有Release
    (*env)->ReleaseIntArrayElements(env, array, c_arr, 0);

    //构造返回数据jdoubleArray
    /*jdouble outArray[] = {sum, average};
    jdoubleArray outJNIArray = (*env)->NewDoubleArray(2);
    if(NULL == outJNIArray) return NULL;
    //向 jdoubleArray 写入数据
    (*env)->SetDoubleArrayRegion(outJNIArray, 0, 2, outArray);*/

    return result;
}

//构建 JNINativeMethod 数组
static JNINativeMethod methods[] = {
        {"operateString3", "(Ljava/lang/String;)Ljava/lang/String;", (void *)operateString3},
        {"sumArray3", "([I)I", (void *)sumArray3},
};

//动态注册的入口函数
jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    //获取JNI env变量
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    //获取java类
    jclass clazz = (*env)->FindClass(env, "org/freedesktop/test/Test");
    if (clazz == NULL) {
        return -1;
    }
    // 动态注册native方法
    if ((*env)->RegisterNatives(env, clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return -1;
    }
    return JNI_VERSION_1_4;
}