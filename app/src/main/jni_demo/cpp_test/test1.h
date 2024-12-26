//
// Created by guoya on 2024/12/19.
//

#ifndef ANDROIDNATIVE_TEST1_H
#define ANDROIDNATIVE_TEST1_H


class Test1 {
public://构造和析构
    //Test1();//构造函数
    //Test1(int i = 0);//构造函数
    //virtual ~Test1();//虚析构函数

public://对外接口
    //void setValue(int i);
    //int getValue();

    /**
     * 打印类型所占字节数
     */
    static void pintDataTypeSize();

    /**
     * 测试get请求
     */
    static void curlGet();

    /**
     * 测试post请求
     */
    static void curlPost();

private://对外隐藏
    //int value;//成员变量
};


#endif //ANDROIDNATIVE_TEST1_H
