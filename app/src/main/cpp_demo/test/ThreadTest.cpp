//
// Created by Adi on 2024/12/30.
//

#include "ThreadTest.h"

ThreadTest::ThreadTest() : ThreadBase("ThreadTest"){

}

void ThreadTest::run() {
    while (isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); //暂停当前线程
        num++;
        LOGD_TAG(TAG, "[%s] working, num=%d", m_name.c_str(), num);

        //回调java层
        JNIEnv *env = JniUtil::getJNIEnv(javaVM, threadKey);
        if (env != nullptr) {
            jstring msg = JniUtil::stringToJstring(env,to_string(num));
            env->CallVoidMethod(app, nativeSetMessageFieldId, msg);
        }
    }
}