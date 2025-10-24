# AndroidNative

## 当前版本选择
AGP8.10.1 Gradle8.11.1 JDK17 Kotlin2.1.20(K2编译器)

NDK版本 27.0.12077973
C++版本 C++14
CMake版本 3.22.1

1. AGP与NDK版本对应
AGP版本	默认NDK版本	备注
8.10.1  27.0.x      #当前选择 NDK27.0.12077973
8.3 	25.x/26.x	
8.0-8.2	25.x
7.4-7.5	23.x-24.x   
7.2-7.3	23.x-24.x
7.1-7.2	21.x-23.x
2. NDK版本与C++版本对应
NDK版本	 支持的C++标准	        
r27   C++20 稳定 / C++23 部分实现
r26   C++20 全面支持 / 实验性 C++23
r25b  C++17 / 大部分 C++20
r24   C++17 完整 / C++20 改进
r23b  C++17 完整 / C++20 部分支持   
r22b  C++17 / 部分 C++20
r21e  C++17 / 实验性 C++20

3. NDK版本与CMake版本对应
NDK版本 最低支持CMake版本 推荐CMake版本
r27    3.22.1     3.25.1、3.27+   
r26    3.18.1     3.22.1、3.25.1  #当前选择 CMake3.22.1
r25	   3.18.1	  3.22.1 或 3.23
r24	   3.18.1	  3.22.1
r23b   3.18.1	  3.22.1
r22	   3.10.2     3.18.1
r21	   3.10.2     3.18.1

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