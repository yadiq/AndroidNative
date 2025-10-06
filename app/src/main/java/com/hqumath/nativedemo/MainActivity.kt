package com.hqumath.nativedemo

import android.os.Bundle
import android.view.View
import androidx.lifecycle.lifecycleScope
import com.hqumath.nativedemo.base.BaseActivity
import com.hqumath.nativedemo.databinding.ActivityMainBinding
import com.hqumath.nativedemo.utils.CommonUtil
import com.hqumath.nativedemo.utils.FileUtil
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.freedesktop.demo.Demo

class MainActivity : BaseActivity() {
    private lateinit var binding: ActivityMainBinding

    override fun initContentView(savedInstanceState: Bundle?): View {
        binding = ActivityMainBinding.inflate(layoutInflater)
        return binding.root
    }

    override fun initListener() {
        //网络请求
        binding.btnHttp.setOnClickListener {
            CommonUtil.toast("发送网络请求")
            binding.tv1.text = "1.curl库发送get post请求，\n2.jsoncpp库处理json，\n结果见日志。"
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
        //测试
        binding.btnTest.setOnClickListener {
            //动态注册的方法
            val result = Demo.registerNatives("123")
            binding.tv1.text = "1.JNI动态注册测试。"
        }
    }

    override fun initData() {
        CommonUtil.init(this)
        //复制assets子文件夹到应用专属目录
        FileUtil.copyAssetsDirToSDCard(mContext, "config")
    }

    override fun initViewObservable() {
    }
}