#include <jni.h>

#include "utils/Util.h"
#include "utils/CurlHttp.h"
#include "utils_android/JniUtil.h"
#include "utils_android/LogUtil.h"
#include "utils_openssl/AesUtil.h"
#include "test/CurlTest.h"
#include "test/TypeTest.h"
#include "test/OpensslTest.h"
#include "test/ThreadTest.h"


//基本数据类型，不需要进行转换，可以直接在 JNI 中使用：
//Java类型 Native类型 c类型           有无符号  JNI签名
//boolean jboolean   unsigned char   uint8_t  Z
//byte	  jbyte	     signed char     int8_t   B
//char	  jchar	     unsigned short  uint16_t C  //注：java中char占两个字节，c中char占一个字节
//short	  jshort	 signed short    int16_t  S
//int	  jint	     int             int32_t  I
//long	  jlong	     long            int64_t  J
//float	  jfloat	 float           int32_t  F
//double  jdouble	 double          int64_t  D
//void    void                                V

//非基本数据类型称为引用类型：
//int[]   jintArray  int*   [I
//byte[]  jbyteArray char*  [B
//String  jstring    char*  Ljava/lang/String;
//Object  jobject           Ljava/lang/Object;
//Class   jclass            Ljava/lang/Class;
//Java自定义类型 Lorg/freedesktop/demo/Demo$OnNativeCallback;

//JNIEnv* 指向JNI环境的指针，可以通过它来访问JNI提供的接口方法:
//jobject Java对象中的this,非静态方法中使用
//jclass Java对象中的this,静态方法中使用
//extern "C" 告诉 C++ 编译器以 C 的方式来编译这个函数，以方便其他 C 程序链接和访问该函数

//jstring是指向JVM内部的一个字符串，不能直接使用，需转为char*后才能使用
//Java中默认是使用UTF-16编码，C/C++默认使用UTF-8编码，需要进行编码转换
//GetStringLength/GetStringUTFLength 获取UTF-16/UTF-8字符串的长度
//NewString/NewStringUTF 构建UTF-16/UTF-8字符串对象

//函数返回值 -1失败 0成功 1特殊成功
//对象实例使用"."操作符，对象指针使用"->"操作符

/////////////工具类方法////////////
//测试网络请求
extern "C" JNIEXPORT jstring JNICALL
curlTest(JNIEnv *env, jclass thiz, jstring jstr) {
    string str = JniUtil::jstringToString(env, jstr);
    CurlHttp::init(); //初始化
    CurlTest curlTest;
    curlTest.curlGet();
    curlTest.curlPost();
    CurlHttp::cleanup(); //清理
    return env->NewStringUTF(str.c_str());
}

//测试加解密
extern "C" JNIEXPORT jstring JNICALL
encryptTest(JNIEnv *env, jclass thiz, jstring plaintextjstr, jstring keyjstr, jstring ivjstr) {
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

//测试数据类型转换
extern "C" JNIEXPORT jstring JNICALL
typeTest(JNIEnv *env, jclass thiz, jstring jstr) {
    //测试
    TypeTest::pintTypeSize();
    TypeTest::typeCast();
    //bytes转hex
    string str = JniUtil::jstringToString(env, jstr);
    string result = Util::bytesToHex(const_cast<char *>(str.c_str()), str.length());
    return env->NewStringUTF(result.c_str());
}

//json配置文件
//JNIEXPORT void JNICALL
//start(JNIEnv *env, jclass thiz, jstring storage_dir_) {
//    string storage_dir = JniUtil::jstringToString(env,storage_dir_);
//    //读取配置文件
//    ConfigManager::getInstance().init(storage_dir);
//    ConfigManager::getInstance().setValue("name", "小王");
//    string name = ConfigManager::getInstance().getValue("name");
//    LOGD("读取name, %s", name.c_str());
//}

/////////////主方法////////////
//用结构体保存变量信息，传递给对象，以执行回调函数
struct CustomData {
    jobject app; //类实例，用来访问它的变量
    ThreadTest *worker; //线程对象
};

//全局变量
jfieldID nativeDataFieldId = nullptr;
jmethodID nativeSetMessageFieldId = nullptr;
JavaVM *javaVM = nullptr;
pthread_key_t threadKey;

//类初始化，缓存java侧的字段id
extern "C" JNIEXPORT void JNICALL
nativeClassInit(JNIEnv *env, jclass thiz) {
    nativeDataFieldId = env->GetFieldID(thiz, "nativeData", "J");
    nativeSetMessageFieldId = env->GetMethodID(thiz, "setMessage", "(Ljava/lang/String;)V");
}

//初始化
extern "C" JNIEXPORT void JNICALL
nativeInit(JNIEnv *env, jobject thiz) {
    //将指针保存到Java侧
    auto *data = new CustomData();
    env->SetLongField(thiz, nativeDataFieldId, reinterpret_cast<jlong>(data));
    //保存变量
    data->app = env->NewGlobalRef(thiz); //保存java类实例
    auto *worker = new ThreadTest();
    data->worker = worker;
    //开始线程
    worker->startThread();

//    LOGD("初始化，对象指针=%p", worker)
//    LOGD("初始化，对象指针=%p", app)
}

//释放
extern "C" JNIEXPORT void JNICALL
nativeRelease(JNIEnv *env, jobject thiz) {
    //从java侧读取指针
    jlong ptr = env->GetLongField(thiz, nativeDataFieldId);
    if (ptr == 0L) {
        return;
    }
    auto *data = reinterpret_cast<CustomData *>(ptr);

//    LOGD("释放，对象指针=%p", worker)
//    LOGD("释放，对象指针=%p", app)

    //结束线程
    data->worker->stopThread();
    //释放对象
    env->DeleteGlobalRef(data->app);
    data->app = nullptr;
    delete data->worker;
    data->worker = nullptr;
    delete data;
    env->SetLongField(thiz, nativeDataFieldId, 0L); //清空指针
}

//构建 JNINativeMethod 数组
static JNINativeMethod methods[] = {
        /////////////工具类方法////////////
        {"curlTest",        "(Ljava/lang/String;)Ljava/lang/String;",                                     (void *) curlTest},
        {"encryptTest",     "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void *) encryptTest},
        {"typeTest",        "(Ljava/lang/String;)Ljava/lang/String;",                                     (void *) typeTest},
        /////////////主方法////////////
        {"nativeClassInit", "()V",                                                                        (void *) nativeClassInit},
        {"nativeInit",      "()V",                                                                        (void *) nativeInit},
        {"nativeRelease",   "()V",                                                                        (void *) nativeRelease},
        //{"setCallback", "(Lorg/freedesktop/demo/Demo$OnNativeCallback;)V", (void *) setCallback},
};

//线程退出时自动调用，从虚拟机中取消注册此线程
void detachCurrentThread(void *env) {
    if (javaVM != nullptr) {
        javaVM->DetachCurrentThread();
    }
}

//动态库 加载入口
extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    //获取JNI env变量
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    //获取native方法所在类
    jclass clazz = env->FindClass("org/freedesktop/demo/Demo");
    if (clazz == nullptr) {
        return JNI_ERR;
    }
    // 动态注册native方法
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        return JNI_ERR;
    }

    javaVM = vm; //保存全局变量
    pthread_key_create(&threadKey, detachCurrentThread); //存储线程本地数据,实现自动清理
    return JNI_VERSION_1_6;
}

//动态库 卸载入口
extern "C" JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {
    pthread_key_delete(threadKey);
}