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
    private val TAG = "Demo"

    ////////////////////////////////////native///////////////////////////////////
    companion object {
        //加载JNI库，仅加载一次
        init {
            System.loadLibrary("crypto")
            System.loadLibrary("demo")
            nativeClassInit()

        }

        //Kotlin 单例实现（懒加载 + 线程安全）
        /*val instance: Demo by lazy(LazyThreadSafetyMode.SYNCHRONIZED) {
            Demo()
        }*/

        @JvmStatic //在java中和jni中调用可不加Companion
        //external对应java中的native，声明由native层实现
        private external fun nativeClassInit(); //初始化java层变量和方法

        /////////////工具类方法////////////
        @JvmStatic
        external fun curlTest(value: String): String //测试网络请求

        @JvmStatic
        external fun encryptTest(plaintext: String, key: String, iv: String): String //测试加解密

        @JvmStatic
        external fun typeTest(value: String): String //测试数据类型转换
    }

//    external fun startThread(): Int //开始线程
//    external fun stopThread() //结束线程
//    external fun setCallback(callback: OnNativeCallback) //设置回调

    private external fun nativeInit()
    private external fun nativeRelease()

    private val nativeData: Long = 0L //缓存c侧对象的指针

    private fun setMessage(message: String) { //native回调，显示文本内容
        LogUtil.d(TAG, "native回调数据: $message")
    }

    ////////////////////////////////////java///////////////////////////////////
    private var listener: OnNativeListener? = null

    fun init(listener: OnNativeListener) {
        this.listener = listener
        nativeInit()
    }

    fun release() {
        nativeRelease()
    }

    interface OnNativeListener {
        fun onInputEvent(type: Int)
    }
}