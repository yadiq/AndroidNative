//
// Created by gyd on 2025/10/27.
//

#ifndef ANDROIDNATIVE_WORKERTHREAD_H
#define ANDROIDNATIVE_WORKERTHREAD_H

#include "ThreadBase.h"
#include "../utils_android/LogUtil.h"

class WorkerThread : public ThreadBase {
public:
    WorkerThread();

protected:
    void run() override;

};


#endif //ANDROIDNATIVE_WORKERTHREAD_H
