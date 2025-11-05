package com.hqumath.nativedemo

import android.os.Bundle
import android.view.View
import androidx.lifecycle.lifecycleScope
import com.hqumath.nativedemo.base.BaseActivity
import com.hqumath.nativedemo.databinding.ActivityMainBinding
import com.hqumath.nativedemo.utils.CommonUtil
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import org.freedesktop.demo.Demo
import org.freedesktop.demo.Demo.OnNativeListener

class MainActivity : BaseActivity() {
    private lateinit var binding: ActivityMainBinding
//    private var demo: Demo? = null
//    private val list = mutableListOf<Demo>()
    private var demo1: Demo? = null
    private var demo2: Demo? = null

    override fun initContentView(savedInstanceState: Bundle?): View {
        binding = ActivityMainBinding.inflate(layoutInflater)
        return binding.root
    }

    override fun initListener() {
        //网络请求
        binding.btnHttp.setOnClickListener {
            CommonUtil.toast("发送网络请求")
            binding.tv1.text = "1.curl库发送get post请求，\n2.nlohmann库处理json，\n结果见日志。"
            lifecycleScope.launch(Dispatchers.IO) { //协程和生命周期能绑定
                Demo.curlTest("")
            }
        }
        //加解密
        binding.btnEncrypt.setOnClickListener {
            val plaintext = "123abc"
            val key = "12345678901234567890123456789012"
            val iv = "1234567890123456"
            val result = Demo.encryptTest(plaintext, key, iv)
            binding.tv1.text =
                "aes256cbc加密:\n  明文: $plaintext\n  密钥: $key\n  偏移量: $iv\n  结果: $result\n更多加解密方式，见日志: \n  aes256gcm、aes256cbc、aes128ecb、\n  sha1、hmacSHA256"
        }
        //数据类型转换
        binding.btnType.setOnClickListener {
            val value = "123abc"
            val result = Demo.typeTest(value)
            binding.tv1.text = "bytes转hex:\n  $value => $result\n更多c++数据类型转换，见日志。"
        }
        //测试线程
        binding.btnStartThread.setOnClickListener {
            lifecycleScope.launch(Dispatchers.IO) {
                if (demo1 == null) {
                    demo1 = Demo()
                    demo1?.init(object : OnNativeListener {
                    override fun onSetMessage(msg: String) {
                        runOnUiThread {
                            binding.tv1.text = "线程回调: $msg"
                        }
                    }
                })
                }
//                val demo = Demo()
//                list.add(demo)
//                demo.init(object : OnNativeListener {
//                    override fun onSetMessage(msg: String) {
//                        runOnUiThread {
//                            binding.tv1.text = "线程回调: $msg"
//                        }
//                    }
//                })
            }
        }
        binding.btnStopThread.setOnClickListener {
            lifecycleScope.launch(Dispatchers.IO) {
                demo1?.release()
                demo1 = null
//                for (item in list) {
//                    item.release()
//                }
//                list.clear()
            }
        }

        binding.btnStartThread2.setOnClickListener {
            lifecycleScope.launch(Dispatchers.IO) {
                if (demo2 == null) {
                    demo2 = Demo()
                    demo2?.init(object : OnNativeListener {
                        override fun onSetMessage(msg: String) {
                            runOnUiThread {
                                binding.tv2.text = "线程回调: $msg"
                            }
                        }
                    })
                }
            }
        }
        binding.btnStopThread2.setOnClickListener {
            lifecycleScope.launch(Dispatchers.IO) {
                demo2?.release()
                demo2 = null
            }
        }
    }

    override fun initData() {
        CommonUtil.init(this)

        //复制assets子文件夹到应用专属目录
        //val filePath = FileUtil.copyAssetsDirToSDCard(mContext, "data")
        //Demo.set_param(filePath)
//        Demo.instance.setCallback(object : OnNativeCallback {
//            override fun onInputEvent(type: Int) {
//                binding.root.post {
//                    binding.tv1.text = "运行中,value=$type"
//                }
//            }
//        })
    }

    override fun initViewObservable() {
    }
}