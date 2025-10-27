//
// Created by gyd on 2025/10/27.
//

#include "ThreadBase.h"

ThreadBase::ThreadBase(const std::string &name)
        : m_name(name), m_running(false) {
    LOGD_TAG(TAG, "[%s] 构造", m_name.c_str());
}

ThreadBase::~ThreadBase() {
    LOGD_TAG(TAG, "[%s] 析构", m_name.c_str());
    stop();
}

bool ThreadBase::start() {
    if (m_running.load()) {
        std::cerr << "[" << m_name << "] Already running.\n";
        return false;
    }
    m_running.store(true);
    m_thread = std::thread(&ThreadBase::threadEntry, this);
    return true;
}

void ThreadBase::stop() {
    if (!m_running.load()) return;
    m_running.store(false);
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

bool ThreadBase::isRunning() const {
    return m_running.load();
}

bool ThreadBase::shouldExit() const {
    return !m_running.load();
}

void ThreadBase::threadEntry() {
    LOGD_TAG(TAG, "[%s] started", m_name.c_str());
    run();
    LOGD_TAG(TAG, "[%s] exited", m_name.c_str());
}
