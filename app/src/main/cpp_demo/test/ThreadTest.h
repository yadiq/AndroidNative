//
// Created by Adi on 2024/12/30.
//

#ifndef ANDROIDNATIVE_THREADTEST_H
#define ANDROIDNATIVE_THREADTEST_H

#include "../nativeGlobals.h"
#include "../base/ThreadBase.h"
#include "../utils_android/LogUtil.h"
#include "../utils_android/JniUtil.h"

class ThreadTest : public ThreadBase {
public:
    ThreadTest();

protected:
    void run() override;

private:
    int num = 0;
};

#endif //ANDROIDNATIVE_THREADTEST_H
