package org.freedesktop.demo;

import com.hqumath.nativedemo.utils.LogUtil;

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2024/12/29 19:26
 * 文件描述:
 * 注意事项:
 * ****************************************************************
 */
public class Demo {
    ////////////////////////////////////native///////////////////////////////////
    static {
        System.loadLibrary("crypto");
        System.loadLibrary("demo");
    }

    public static native String curlTest(String value);
    public static native String encrypt(String value);
    public static native String type(String value);
    public static native String test1(String value);
    //动态注册的方法
    public static native String registerNatives(String value);

    public native void thread1();

    private void javaCallback(int count) {
        LogUtil.e(TAG, "onNativeCallBack : " + count);
    }

    ////////////////////////////////////java///////////////////////////////////
    private final String TAG = "Native";

}
