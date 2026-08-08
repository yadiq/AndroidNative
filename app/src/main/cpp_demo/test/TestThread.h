//
// Created by gyd on 2026/8/8.
//

#pragma once

#include <jni.h>
#include "../base/ThreadBase.h"

class TestThread : public ThreadBase
{
public:
    TestThread(jobject app);
    virtual ~TestThread() override;

protected:
    /// 子类实现线程主逻辑
    virtual void run() override;

private:
    int num = 0;
    jobject app;
};