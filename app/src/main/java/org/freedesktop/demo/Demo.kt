package org.freedesktop.demo

import com.hqumath.nativedemo.utils.LogUtil

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2025/10/5 22:18
 * 文件描述:
 * 注意事项:
 * ****************************************************************
 */
class Demo {
    ////////////////////////////////////native///////////////////////////////////
    companion object {
        init {
            System.loadLibrary("crypto")
            System.loadLibrary("demo")
        }

        @JvmStatic //在java中和jni中调用可不加 Companion
        external fun curlTest(value: String): String

        @JvmStatic
        external fun encryptTest(plaintext: String, key: String, iv: String): String

        @JvmStatic
        external fun typeTest(value: String): String

        @JvmStatic
        external fun test1(value: String): String

        //动态注册的方法
        @JvmStatic
        external fun registerNatives(value: String): String
    }

    external fun thread1()

    private fun javaCallback(count: Int) {
        LogUtil.e(TAG, "onNativeCallBack : $count")
    }

    ////////////////////////////////////java///////////////////////////////////
    private val TAG = "Native"

}