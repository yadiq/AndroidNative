package com.hqumath.nativedemo;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hqumath.nativedemo.databinding.ActivityMainBinding;
import com.hqumath.nativedemo.utils.CommonUtil;
import com.hqumath.nativedemo.utils.LogUtil;

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

        //格式化字符串
        //StringUtil.stringToArray("ivrealfly0241116");

        binding.btn1.setOnClickListener(v -> {
            //加密
        /*String encrypt = Lianjing.method01("123456789012345");
        LogUtil.d("encrypt： " + encrypt);
        String decrypt = Lianjing.method02(encrypt);
        LogUtil.d("decrypt： " + decrypt);*/
            //网络请求
            String response = Demo.httpget("http://httpbin.org/get?param1=value1");
            LogUtil.d(TAG, "java response\n" + response);
        });
        binding.btn1.performClick();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        CommonUtil.killProgress();
    }
}
