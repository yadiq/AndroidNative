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
class Demo private constructor(){
    ////////////////////////////////////native///////////////////////////////////
    companion object {
        //加载 JNI 库，仅加载一次
        init {
            System.loadLibrary("crypto")
            System.loadLibrary("demo")
        }

        //Kotlin 单例实现（懒加载 + 线程安全）
        val instance: Demo by lazy(LazyThreadSafetyMode.SYNCHRONIZED) {
            Demo()
        }

        @JvmStatic //在java中和jni中调用可不加 Companion
        external fun curlTest(value: String): String //测试网络请求

        @JvmStatic
        external fun encryptTest(plaintext: String, key: String, iv: String): String //测试加解密

        @JvmStatic
        external fun typeTest(value: String): String //测试数据类型转换
    }

    external fun startThread(): Int //开始线程
    external fun stopThread() //结束线程
    external fun setCallback(callback: OnNativeCallback) //设置回调

    ////////////////////////////////////java///////////////////////////////////
    interface OnNativeCallback{
        fun onInputEvent(type: Int)

    }
}