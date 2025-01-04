package com.hqumath.nativedemo;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hqumath.nativedemo.databinding.ActivityMainBinding;
import com.hqumath.nativedemo.utils.CommonUtil;

import org.freedesktop.demo.Demo;

/**
 * ****************************************************************
 * 作    者: Created by gyd
 * 创建时间: 2023/9/5 16:24
 * 文件描述:
 * 注意事项:
 * ****************************************************************
 */
public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;
    private final String TAG = "Native";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        CommonUtil.init(this);

        //网络请求
        binding.btnHttp.setOnClickListener(v -> {
            CommonUtil.toast("发送网络请求");
            binding.tv1.setText("1.curl库发送get post请求，\n2.jsoncpp库处理json，\n结果见日志。");
            Demo.curlTest("");
        });

        //加解密
        binding.btnEncrypt.setOnClickListener(v -> {
            String plaintext = "123abc";
            String key = "12345678901234567890123456789012";
            String iv = "1234567890123456";
            String result = Demo.encryptTest(plaintext, key, iv);
            binding.tv1.setText("aes256cbc加密:\n  明文: " + plaintext + "\n  密钥: " + key + "\n  偏移量: " + iv + "\n  结果: " + result + "\n更多加解密方式，见日志: \n  aes256gcm、aes256cbc、aes128ecb、\n  sha1、hmacSHA256");
        });

        //数据类型转换
        binding.btnType.setOnClickListener(v -> {
            String value = "123abc";
            String result = Demo.typeTest(value);
            binding.tv1.setText("bytes转hex:\n  " + value + " => " + result + "\n更多c++数据类型转换，见日志。");
        });

        //测试
        binding.btnTest.setOnClickListener(v -> {
            //动态注册的方法
            String result = Demo.registerNatives("123");
            binding.tv1.setText("1.JNI动态注册测试。");

        });


        //格式化字符串
        //StringUtil.stringToArray("ivrealfly0241116");
        //多线程
        //Demo demo = new Demo();
        //demo.thread1();


//        binding.btn2.setOnClickListener(v -> {
//            //加密
//        /*String encrypt = Lianjing.method01("123456789012345");
//        LogUtil.d("encrypt： " + encrypt);
//        String decrypt = Lianjing.method02(encrypt);
//        LogUtil.d("decrypt： " + decrypt);*/
//        });

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        CommonUtil.killProgress();
    }
}
