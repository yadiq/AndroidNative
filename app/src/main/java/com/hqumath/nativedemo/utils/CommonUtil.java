package com.hqumath.nativedemo.utils;

import static android.content.Context.TELEPHONY_SERVICE;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.StringRes;

import java.io.ByteArrayOutputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * 常用工具类
 */
public class CommonUtil {

    @SuppressLint("StaticFieldLeak")
    private static Context context;

    private CommonUtil() {
        throw new UnsupportedOperationException("u can't instantiate me...");
    }

    /**
     * 初始化工具类
     *
     * @param context 上下文
     */
    public static void init(@NonNull final Context context) {
        CommonUtil.context = context.getApplicationContext();
    }

    /**
     * 获取ApplicationContext
     *
     * @return ApplicationContext
     */
    public static Context getContext() {
        if (context != null) {
            return context;
        }
        throw new NullPointerException("should be initialized in application");
    }

    public static void toast(String s){
        Toast.makeText(CommonUtil.getContext(), s, Toast.LENGTH_SHORT).show();
    }

    public static void toast(@StringRes int resId) {
        Toast.makeText(context, resId, Toast.LENGTH_SHORT).show();
    }

    //获取版本号
    public static String getVersion() {
        try {
            PackageInfo pi = context.getPackageManager().getPackageInfo(context.getPackageName(), 0);
            return pi.versionName;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
            return "";
        }
    }

    //获取imei
    public static String getIMEI() {
        String imei = "";
        try {
            TelephonyManager tm = (TelephonyManager) context.getSystemService(TELEPHONY_SERVICE);
            imei = tm.getDeviceId();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return imei;
    }

    public static void showKeyboard(Activity activity, EditText editText) {
        InputMethodManager inputMethodManager = (InputMethodManager) activity.getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.showSoftInput(editText, 0);
    }

    public static void closeKeyboard(Activity activity) {
        View view = activity.getWindow().peekDecorView();
        if (view != null) {
            InputMethodManager inputMethodManager = (InputMethodManager) activity.getSystemService(Context.INPUT_METHOD_SERVICE);
            inputMethodManager.hideSoftInputFromWindow(view.getWindowToken(), 0);
        }
    }

    public static String MapToString(HashMap<String, String> map) {
        Iterator<Map.Entry<String, String>> i = map.entrySet().iterator();
        if (!i.hasNext())
            return "{}";

        StringBuilder sb = new StringBuilder();
        sb.append('{');
        for (; ; ) {
            Map.Entry<String, String> e = i.next();
            String key = e.getKey();
            String value = e.getValue();
            sb.append(key);
            sb.append(':');
            sb.append(value);
            if (!i.hasNext())
                return sb.append('}').toString();
            sb.append(',');//.append(' ');
        }
    }

    /**
     * 检查是否有网络
     */
    public static boolean isNetworkAvailable() {
        ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = cm.getActiveNetworkInfo();
        return info != null && info.isAvailable();
    }

    //String 转 map
    public static HashMap<String, String> String2HashMap(String data) {
        int start = data.indexOf("{");
        int end = data.indexOf("}");
        String data0 = data.substring(start + 1, end);
        HashMap<String, String> hashMap = new LinkedHashMap<>();
        String[] data1 = data0.split(",");
        for (String data2 : data1) {
            String[] data3 = data2.split(":");
            if (data3.length == 2) {
                hashMap.put(data3[0].trim().replace("\"", ""), data3[1].trim().replace("\"", ""));
            } else if (data3.length == 1) {
                hashMap.put(data3[0].trim().replace("\"", ""), "");
            }
        }
        return hashMap;
    }

    /**
     * Base64字符串转换成图片
     *
     * @param string
     * @return
     */
    public static Bitmap stringToBitmap(String string) {
        Bitmap bitmap = null;
        try {
            byte[] bitmapArray = Base64.decode(string, Base64.DEFAULT);
            bitmap = BitmapFactory.decodeByteArray(bitmapArray, 0, bitmapArray.length);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return bitmap;
    }

    /**
     * 图片转换成base64字符串
     *
     * @param bitmap
     * @return
     */
    public static String bitmapToString(Bitmap bitmap) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, baos);
        byte[] imgBytes = baos.toByteArray();// 转为byte数组
        return Base64.encodeToString(imgBytes, Base64.DEFAULT);
    }

    // 计算字符串的MD5
    public static String md5(String plainText) {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(plainText.getBytes());
            byte b[] = md.digest();
            int i;
            StringBuffer buf = new StringBuffer("");
            for (int offset = 0; offset < b.length; offset++) {
                i = b[offset];
                if (i < 0)
                    i += 256;
                if (i < 16)
                    buf.append("0");
                buf.append(Integer.toHexString(i));
            }
            // 32位加密
            return buf.toString();
            // 16位的加密
//             return buf.toString().substring(8, 24);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return null;
        }
    }

    //设置window全屏
    public static void fullScreenImmersive(View view){
        int flags = View.SYSTEM_UI_FLAG_FULLSCREEN //状态栏隐藏
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION //导航栏隐藏
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY //状态栏或导航栏恢复状态后只显示一小段时间
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE //布局稳定
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN //状态栏不占位
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION; //导航栏不占位
        view.setSystemUiVisibility(flags);
    }

    /**
     * app退出后杀死当前进程
     * 解决问题：glide缓存问题 gstreamer释放问题
     */
    public static void killProgress() {
        String packageName = context.getPackageName();
        ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        try {
            am.killBackgroundProcesses(packageName);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /********防止按钮连续点击********/
    private static long lastClickTime;
    public synchronized static boolean isFastClick() {
        long time = System.currentTimeMillis();
        if (time - lastClickTime < 500) {
            return true;
        }
        lastClickTime = time;
        return false;
    }
}
