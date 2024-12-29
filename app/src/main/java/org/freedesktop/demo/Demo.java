package org.freedesktop.demo;

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

    public static native String encrypt(String value);

    public static native String httpget(String value);

    public static native String type(String value);

    public static native String test1(String value);


    ////////////////////////////////////java///////////////////////////////////
//    private final String TAG = "JNI_log";

}
