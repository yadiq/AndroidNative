//
// Created by Adi on 2024/12/30.
//

#ifndef ANDROIDNATIVE_THREADTEST_H
#define ANDROIDNATIVE_THREADTEST_H

#include "../base/ThreadBase.h"
#include "../utils_android/LogUtil.h"
#include "../utils_android/JniInterface.h"

class ThreadTest : public ThreadBase {
public:
    ThreadTest();

protected:
    void run() override;

private:
    JniInterface mJniInterface;
    int num = 0;
};

#endif //ANDROIDNATIVE_THREADTEST_H
