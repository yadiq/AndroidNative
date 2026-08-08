//
// Created by gyd on 2026/8/8.
//

#include "TestThread.h"
#include "../utils_android/LogUtil.h"
#include "../utils_android/JniUtil.h"
#include "../nativeGlobals.h"

TestThread::TestThread(jobject app)
        : ThreadBase("TestThread")
        , app(app)
{
}

TestThread::~TestThread()
{
    //基类析构会自动 stop+join，这里一般不用写额外代码
}

void TestThread::run()
{
    while (!shouldStop())
    {
        //Util::Log("%s, doing work...", m_threadName.c_str());
        waitFor(std::chrono::milliseconds(1000));
        num++;
        LOGD_FILE("%s, working, num=%d", m_threadName.c_str(), num);

        //回调java层
        JNIEnv *env = JniUtil::getJNIEnv(javaVM, threadKey);
        if (env != nullptr && app != nullptr) {
//            LOGD("线程中，对象指针=%p", app)
            jstring msg = JniUtil::stringToJstring(env, to_string(num));
            env->CallVoidMethod(app, nativeSetMessageFieldId, msg);
        }
    }
}