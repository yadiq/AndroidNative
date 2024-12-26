package com.hqumath.nativedemo;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.hqumath.nativedemo.databinding.ActivityMainBinding;
import com.hqumath.nativedemo.utils.CommonUtil;
import com.hqumath.nativedemo.utils.LogUtil;

import org.freedesktop.test.Test;

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

    //音频编解码器
    byte[] data = new byte[240];//每次收到的数据240B
    byte[] encodeData = new byte[240];//编码后的数据240B
    byte[] decodeData = new byte[1600];//解码后大小480B

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        CommonUtil.init(this);

        //格式化字符串
        //StringUtil.stringToArray("ivrealfly0241116");
        //加密
        /*String encrypt = Lianjing.method01("123456789012345");
        LogUtil.d("encrypt： " + encrypt);
        String decrypt = Lianjing.method02(encrypt);
        LogUtil.d("decrypt： " + decrypt);*/

        binding.btn1.setOnClickListener(v -> {
            String result1 = Test.test1();
            LogUtil.d(TAG, result1);
            String result2 = Test.test2("123");
            LogUtil.d(TAG, result2);

        });
        binding.btn1.performClick();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        CommonUtil.killProgress();
    }
}
