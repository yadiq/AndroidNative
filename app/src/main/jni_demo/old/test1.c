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


//c函数：
//strcpy() 字符串复制
//strcat() 字符串拼接


//字符串操作
//jstring是指向JVM内部的一个字符串，不能直接使用，需转为char*后才能使用
//Java中默认是使用UTF-16编码，C/C++默认使用UTF-8编码，需要进行编码转换
//GetStringLength/GetStringUTFLength 获取UTF-16/UTF-8字符串的长度
//NewString/NewStringUTF 构建UTF-16/UTF-8字符串对象

JNIEXPORT jstring JNICALL
Java_org_freedesktop_test_Test_operateString1(JNIEnv *env, jobject thiz, jstring str) {
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
Java_org_freedesktop_test_Test_sumArray1(JNIEnv *env, jobject thiz, jintArray array) {
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

/////////////////////////////////////多线程//////////////////////////////////////
static int count1 = 10;
static int count2 = 20;
JavaVM *gJavaVM = NULL;//全局 JavaVM 变量, 用于获取环境变量env
//JavaVM是虚拟机VM在JNI中的表示,一个进程JVM中只有一个JavaVM对象，这个对象是线程共享的
jobject gJavaObj = NULL;//全局 Jobject 变量, 用于存储jobject thiz
jmethodID methodId = NULL;//全局的方法ID

//这里通过标志位来确定 两个线程的工作都完成了再执行 DeleteGlobalRef
//当然也可以通过加锁实现
bool main_finished = false;
bool background_finished = false;

//多线程-执行
static void *native_thread_exec(void *arg) {

    LOGE("nativeThreadExec");
    LOGE("The pthread id : %d\n", pthread_self());
    JNIEnv *env;
    //从全局的JavaVM中获取到环境变量
    //附加当前线程到虚拟机VM当中，向虚拟机分配线程独立的env，之后GetEnv返回的env才有值
    (*gJavaVM)->AttachCurrentThread(gJavaVM, &env, NULL);

    //线程循环
    for (int i = 0; i < 5; i++) {
        usleep(2);
        //跨线程回调Java层函数
        (*env)->CallVoidMethod(env, gJavaObj, methodId, count2++);
    }

    background_finished = true;

    if (main_finished && background_finished) {
        (*env)->DeleteGlobalRef(env, gJavaObj);
        LOGE("全局引用在子线程销毁");
    }
    (*gJavaVM)->DetachCurrentThread(gJavaVM);

    return ((void *) 0);

}

//多线程
JNIEXPORT void JNICALL
Java_org_freedesktop_test_Test_thread1(JNIEnv *env, jobject thiz) {
    //创建全局引用，方便其他函数或线程使用
    gJavaObj = (*env)->NewGlobalRef(env, thiz);
    jclass class = (*env)->GetObjectClass(env, thiz);
    methodId = (*env)->GetMethodID(env, class, "javaCallback", "(I)V");
    (*env)->DeleteLocalRef(env, class);

    //保存全局 JavaVM，注意 JavaVM 不是 JNI 引用类型
    (*env)->GetJavaVM(env, &gJavaVM);

    pthread_t id;
    if (pthread_create(&id, NULL, native_thread_exec, NULL) != 0) {
        return;
    }

    for (int i = 0; i < 5; i++) {
        usleep(20);//把进程挂起一段时间 μs
        //回调Java层函数
        (*env)->CallVoidMethod(env, gJavaObj, methodId, count1++);
    }

    main_finished = true;
    if (main_finished && background_finished && !(*env)->IsSameObject(env, gJavaObj, NULL)) {
        (*env)->DeleteGlobalRef(env, gJavaObj);
        LOGE("全局引用在主线程销毁");
    }
}





