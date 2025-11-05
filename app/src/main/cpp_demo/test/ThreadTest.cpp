//
// Created by Adi on 2024/12/30.
//

#include "ThreadTest.h"

ThreadTest::ThreadTest() : ThreadBase("ThreadTest") {

}

void ThreadTest::threadProc() {
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); //暂停当前线程
        num++;
        LOGD_TAG("ThreadBase", "[%s] working, num=%d", m_name.c_str(), num);

        //回调java层
//        JNIEnv *env = JniUtil::getJNIEnv(javaVM, threadKey);
//        if (env != nullptr && app != nullptr) {
////            LOGD("线程中，对象指针=%p", app)
//
//            jstring msg = JniUtil::stringToJstring(env, to_string(num));
//            env->CallVoidMethod(app, nativeSetMessageFieldId, msg);
//        }
    }
}
