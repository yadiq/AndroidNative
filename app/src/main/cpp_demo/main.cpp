#include <jni.h>
#include <string>
#include <unistd.h>

#include "utils/Util.h"
#include "utils/CurlHttp.h"
#include "utils_android/JniUtil.h"
#include "utils_android/LogUtil.h"
#include "test_curl/CurlTest.h"
#include "test_type/TypeTest.h"
#include "test/OpensslTest.h"
#include "utils_openssl/AesUtil.h"

//JNIEnv* 指向JNI环境的指针，可以通过它来访问JNI提供的接口方法:
//jobject Java对象中的this
//jclass Java对象中的this,静态方法中使用

//基本数据类型，不需要进行转换，可以直接在 JNI 中使用：
//Java类型 Native类型 c类型           有无符合 字长
//boolean jboolean   unsigned char   uint8_t
//byte	  jbyte	     signed char     int8_t
//char	  jchar	     unsigned short  uint16_t
//short	  jshort	 signed short    int16_t
//int	  jint	     int             int32_t
//long	  jlong	     long            int64_t
//float	  jfloat	 float           int32_t
//double  jdouble	 double          int64_t
//注：java中char占两个字节，c中char占一个字节

//非基本数据类型称为引用类型：
//string  jstring    char*
//int[]   jintArray  int*
//byte[]  jbyteArray char*

//jstring是指向JVM内部的一个字符串，不能直接使用，需转为char*后才能使用
//Java中默认是使用UTF-16编码，C/C++默认使用UTF-8编码，需要进行编码转换
//GetStringLength/GetStringUTFLength 获取UTF-16/UTF-8字符串的长度
//NewString/NewStringUTF 构建UTF-16/UTF-8字符串对象

//extern "C" 告诉 C++ 编译器以 C 的方式来编译这个函数，以方便其他 C 程序链接和访问该函数

JavaVM *gJavaVM = NULL;//全局 JavaVM 变量, 用于获取环境变量env
//JavaVM是虚拟机VM在JNI中的表示,一个进程JVM中只有一个JavaVM对象，这个对象是线程共享的
jobject gJavaObj = NULL;//全局 Jobject 变量, 用于存储jobject thiz
jmethodID methodId = NULL;//全局的方法ID

//这里通过标志位来确定 两个线程的工作都完成了再执行 DeleteGlobalRef
//当然也可以通过加锁实现
bool main_finished = false;
bool background_finished = false;

//网络请求
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_curlTest(JNIEnv *env, jclass thiz, jstring jstr) {
    string str = JniUtil::jstringToString(env, jstr);
    //网络请求
    CurlHttp::init();
    CurlTest curlTest;
    curlTest.curlGet();
    curlTest.curlPost();
    CurlHttp::cleanup();
    return env->NewStringUTF(str.c_str());
}

//加解密
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_encryptTest(JNIEnv *env, jclass thiz, jstring plaintextjstr, jstring keyjstr, jstring ivjstr) {
    //测试
    OpensslTest::base64();
    OpensslTest::aes();
    OpensslTest::sha();
    //aes256cbc加密
    string plaintext = JniUtil::jstringToString(env, plaintextjstr);
    string key = JniUtil::jstringToString(env, keyjstr);
    string iv = JniUtil::jstringToString(env, ivjstr);
    string aes256cbcEncrypt = AesUtil::aes256cbcEncrypt(plaintext.c_str(), key.c_str(), iv.c_str());
    return env->NewStringUTF(aes256cbcEncrypt.c_str());
}

//数据类型转换
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_typeTest(JNIEnv *env, jclass thiz, jstring jstr) {
    //测试
    TypeTest::pintTypeSize();
    TypeTest::typeCast();
    //bytes转hex
    string str = JniUtil::jstringToString(env, jstr);
    string result = Util::bytesToHex(const_cast<char *>(str.c_str()), str.length());
    return env->NewStringUTF(result.c_str());
}

//测试
extern "C" JNIEXPORT jstring JNICALL
Java_org_freedesktop_demo_Demo_test1(JNIEnv *env, jclass thiz, jstring jstr) {
    std::string hexStr = "Hello from C++";
    return env->NewStringUTF(hexStr.c_str());
}

//多线程-执行
static void *native_thread_exec(void *arg) {
    LOGE("nativeThreadExec");
    LOGE("The pthread id : %ld\n", pthread_self());

    //获取环境变量
    JNIEnv *env = JniUtil::getEnv(gJavaVM);
    if (env == NULL)
        return ((void *) 0);

    for (int i = 0; i < 5; i++) {
        usleep(2);
        //跨线程回调Java层函数
        env->CallVoidMethod(gJavaObj, methodId, i);
    }

    background_finished = true;
    if (main_finished && background_finished) {
        env->DeleteGlobalRef(gJavaObj);
        LOGE("全局引用在子线程销毁");
    }

    JniUtil::releaseEnv(gJavaVM);
    return ((void *) 0);
}

//多线程
extern "C" JNIEXPORT void JNICALL
Java_org_freedesktop_demo_Demo_thread1(JNIEnv *env, jobject thiz) {
    //全局 JavaVM 变量, 用于获取环境变量env
    env->GetJavaVM(&gJavaVM);
    //全局 Jobject 变量, 用于存储jobject thiz
    gJavaObj = env->NewGlobalRef(thiz);
    //全局的方法ID
    jclass jclass = env->GetObjectClass(thiz);
    methodId = env->GetMethodID(jclass, "javaCallback", "(I)V");
    env->DeleteLocalRef(jclass);

    pthread_t id;
    if (pthread_create(&id, NULL, native_thread_exec, NULL) != 0) {
        return;
    }

    for (int i = 10; i < 55; i++) {
        usleep(20);//把进程挂起一段时间 μs
        //回调Java层函数
        env->CallVoidMethod(gJavaObj, methodId, i);
    }

    main_finished = true;
    if (main_finished && background_finished && !env->IsSameObject(gJavaObj, NULL)) {
        env->DeleteGlobalRef(gJavaObj);
        LOGE("全局引用在主线程销毁");
    }
}