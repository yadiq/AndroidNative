#include <string.h>
#include <jni.h>
#include <android/log.h>

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>


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





