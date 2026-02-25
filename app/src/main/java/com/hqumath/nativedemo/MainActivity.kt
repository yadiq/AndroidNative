package com.hqumath.nativedemo

import android.os.Bundle
import android.view.SurfaceHolder
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

        private var demo: Demo? = null
//    private val list = mutableListOf<Demo>()
//    private var demo1: Demo? = null
//    private var demo2: Demo? = null

    override fun initContentView(savedInstanceState: Bundle?): View {
        binding = ActivityMainBinding.inflate(layoutInflater)
        return binding.root
    }

    override fun initListener() {
        binding.btnTest.setOnClickListener {
            val msg = Demo.test("")
            binding.tvMsg.text = msg
        }
        //网络请求
//        binding.btnHttp.setOnClickListener {
////            CommonUtil.toast("发送网络请求")
////            binding.tv1.text = "1.curl库发送get post请求，\n2.nlohmann库处理json，\n结果见日志。"
////            lifecycleScope.launch(Dispatchers.IO) { //协程和生命周期能绑定
////                Demo.curlTest("")
////            }
//            val msg = Demo.curlTest("")
//            binding.btnHttp.text = msg
//        }
//        //数据类型转换
//        binding.btnType.setOnClickListener {
//            val value = "123abc"
//            val result = Demo.typeTest(value)
//            binding.tv1.text = "bytes转hex:\n  $value => $result\n更多c++数据类型转换，见日志。"
//        }
//        //测试线程
//        binding.btnStartThread.setOnClickListener {
//            lifecycleScope.launch(Dispatchers.IO) {
//                if (demo1 == null) {
//                    demo1 = Demo()
//                    demo1?.init(object : OnNativeListener {
//                        override fun onSetMessage(msg: String) {
//                            runOnUiThread {
//                                binding.tv1.text = "线程回调: $msg"
//                            }
//                        }
//                    })
//                }
//            }
//        }
//        binding.btnStopThread.setOnClickListener {
//            binding.btnStopThread.isEnabled = false
//            lifecycleScope.launch(Dispatchers.IO) {
//                if (demo1 != null) {
//                    demo1?.release()
//                    demo1 = null
//                    runOnUiThread {
//                        binding.tv1.text = "线程已经释放"
//                        binding.btnStopThread.isEnabled = true
//                    }
//                }
//            }
//        }
    }

    override fun initData() {
        CommonUtil.init(this)

        demo = Demo()
        binding.surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                demo?.setSurface(holder.surface)
                demo?.play("rtmp://192.168.0.32:1935/live/stream")
//                demo?.play("rtmp://ns8.indexforce.com/home/mystream")
            }

            override fun surfaceChanged(
                p0: SurfaceHolder,
                p1: Int,
                p2: Int,
                p3: Int,
            ) {
            }

            override fun surfaceDestroyed(p0: SurfaceHolder) {
                demo?.stop()
            }
        })
    }

    override fun initViewObservable() {
    }
}