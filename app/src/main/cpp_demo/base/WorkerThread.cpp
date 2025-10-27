//
// Created by gyd on 2025/10/27.
//

#include "WorkerThread.h"

WorkerThread::WorkerThread() : ThreadBase("WorkerThread"){

}

void WorkerThread::run() {
    while (!shouldExit()) {
        LOGD_TAG(TAG, "[%s] working...", m_name.c_str());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

