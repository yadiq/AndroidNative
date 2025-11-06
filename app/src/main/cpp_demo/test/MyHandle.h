//
// Created by gyd on 2025/11/5.
//

#ifndef ANDROIDNATIVE_MYHANDLE_H
#define ANDROIDNATIVE_MYHANDLE_H

#include "../base/ThreadBase.h"

class MyHandle : public ThreadBase {
public:
    MyHandle(jobject app);

//    explicit MyHandle(MyHandle *myHandle); //显式构造函数
    ~MyHandle() override; //重写了基类的虚析构函数
protected:
    void threadProc() override;

private:
    int num = 0;
    jobject app;
};

#endif //ANDROIDNATIVE_MYHANDLE_H
