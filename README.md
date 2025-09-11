# AndroidNative

## 版本选择
AGP7.4.2 Gradle7.6 JDK17 Kotlin1.9.22

NDK版本 23.1.7779620 
C++版本 C++14

1. AGP与NDK版本对应
Android Studio版本	  AGP版本	默认NDK版本	备注
Android Studio Hedgehog	8.3+	25.x/26.x	
Android Studio Giraffe	8.0-8.2	25.x
Android Studio Flamingo	7.4-7.5	23.x-24.x   #选择
Android Studio Electric Eel	7.2-7.3	23.x-24.x
Android Studio Dolphin	7.1-7.2	21.x-23.x
2. NDK版本与C++版本对应
NDK版本	 支持的C++标准	        默认标准	备注
NDK r26+ C++17, C++14, C++11	C++17	
NDK r23	 C++17, C++14, C++11	C++14   #选择
NDK r21	 C++17, C++14, C++11	C++14

NDK版本	支持的最高CMake版本 推荐CMake版本 备注
NDK r26+    3.22.1+	    3.22.1	
NDK r25	    3.22.1	    3.22.1
NDK r24	    3.21.1	    3.18.1
NDK r23	    3.20.1	    3.18.1        #选择
NDK r22	    3.19.6	    3.18.1
NDK r21	    3.18.1	    3.18.1	

## 介绍
Android 原生开发。
1. 使用 OpenSSL 实现加密算法。
2. 使用 Curl+JsonCpp 实现http请求。

## 使用 OpenSSL 实现加密算法
1. 加密算法包括 
aes_256_gcm、aes_256_cbc、aes_128_ecb、SHA-1、HMAC算法。
2. 实现原理见博客
https://yadiq.github.io/2024/07/03/AndroidOpensslEncrypt/

## 使用 Curl+JsonCpp 实现http请求
1. 功能 
使用JsonCpp实现Json转string 和 string转Json
使用curl实现 http get请求 和 post请求。
2. 实现原理见博客
https://yadiq.github.io/2024/07/04/AndroidCurlHttp/

## 效果图

![AndroidOpensslEncrypt.png](img/AndroidOpensslEncrypt.png)