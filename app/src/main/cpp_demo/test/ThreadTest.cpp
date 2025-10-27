//
// Created by Adi on 2024/12/30.
//

#include "ThreadTest.h"

ThreadTest::ThreadTest() : ThreadBase("ThreadTest"){

}

void ThreadTest::run() {
    while (!shouldExit()) {
        LOGD_TAG(TAG, "[%s] working...", m_name.c_str());
        std::this_thread::sleep_for(std::chrono::seconds(1)); //暂停当前线程
        num++;
        mJniInterface.onInputEvent(num);
    }
}