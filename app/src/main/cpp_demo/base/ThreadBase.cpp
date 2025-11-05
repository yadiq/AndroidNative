//
// Created by gyd on 2025/10/27.
//

#include "ThreadBase.h"

#include <utility>

//值传递。不拷贝，提高性能 std::move（C++11+ 推荐）
ThreadBase::ThreadBase(std::string name)
        : m_name(std::move(name)), m_running(false) { //成员初始化列表
    LOGD_FILE("[%s] 构造", m_name.c_str());
}

ThreadBase::~ThreadBase() {
    LOGD_FILE("[%s] 析构", m_name.c_str());
    stopThread();
}

bool ThreadBase::startThread() {
    if (m_running.load()) {
        return false;
    }
    m_running.store(true);
    m_thread = std::thread(&ThreadBase::threadEntry, this);
    return true;
}

void ThreadBase::stopThread() {
    if (!m_running.load()) return;
    m_running.store(false);
    LOGD_FILE("[%s] stop", m_name.c_str());
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

bool ThreadBase::isRunning() const {
    return m_running.load();
}

void ThreadBase::threadEntry() {
    LOGD_FILE("[%s] started", m_name.c_str());
    threadProc();
    LOGD_FILE("[%s] exited", m_name.c_str());
}
