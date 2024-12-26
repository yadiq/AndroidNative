package org.freedesktop.test;

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2023/9/5 16:13
 * 文件描述:
 * 注意事项:
 * ****************************************************************
 */
public class Test {
    ////////////////////////////////////native///////////////////////////////////
    static {
        System.loadLibrary("crypto");
        System.loadLibrary("ssl");
        System.loadLibrary("test");
    }

    public static native String test1();

    public static native String test2(String value);

//    public native String operateString1(String value);
//
//    public native int sumArray1(int[] value);
//
//    public native String operateString2(String value);
//
//    public native int sumArray2(int[] value);
//
//    public native String operateString3(String value);
//
//    public native int sumArray3(int[] value);
//
//    public native void thread1();
//
//    private void javaCallback(int count) {
//        LogUtil.e(TAG, "onNativeCallBack : " + count);
//    }


    ////////////////////////////////////java///////////////////////////////////
//    private final String TAG = "JNI_log";

}
