# AndroidNative

## 当前版本选择(NDK27.0代码调试速度慢，所以降低版本)
AGP8.3.2 Gradle8.4 NDK25.2.9519653 JDK17
Kotlin2.1.20(K2编译器)
C++版本 C++14
CMake版本 3.22.1

## 最新版本选择(最佳性能,最新版本的速度更快)
AGP8.10.1 Gradle8.11.1 NDK27.0.12077973 JDK17
Kotlin2.1.20(K2编译器)
C++版本 C++14
CMake版本 3.30.3

## 旧版本选择(稳定兼容,长期支持版本)
AGP7.4.2 Gradle7.6 NDK23.1 JDK11
Kotlin1.9.22
C++版本 C++14
CMake版本 3.22.1

## 工具说明
AGP   构建系统层。构建系统插件，协调所有编译任务
CMake 构建工具层。负责生成本地 (Native) C/C++ 的编译规则
NDK   编译工具链层。编译 C/C++ 代码


## AGP发布信息
[官方文档](https://developer.android.google.cn/build/releases/past-releases/agp-8-10-0-release-notes)
1. AGP8.10
子版本：8.10.0 8.10.1
默认版本：Gradle8.11.1 SDK35.0 NDK27.0 JDK17

2. AGP8.3
子版本：8.3.0 8.3.1 8.3.2
默认版本：Gradle8.4 SDK34.0 NDK25.1 JDK17

2. AGP8.0
子版本：8.0.0 8.0.1 8.0.2
默认版本：Gradle8.0 SDK30.0 NDK25.1 JDK17

3. AGP7.4
子版本：7.4.0 7.4.1 7.4.2
默认版本：Gradle7.5 SDK30.0 NDK23.1 JDK11

4. AGP7.0
子版本：7.0.0 7.0.1
默认版本：Gradle7.0.2 SDK30.0 NDK21.4 JDK11

## 版本对应关系
[官方文档](https://developer.android.google.cn/build/releases/gradle-plugin?hl=zh-cn#updating-gradle)
1. AGP 与 Gradle
+ AGP版本   最低Gradle版本
+ 8.13     8.13
+ 8.12     8.13
+ 8.11     8.13
+ 8.10     8.11.1  #当前选择8.10.1
...
+ 8.6      8.7
+ 8.5      8.7
...
+ 8.0      8.0
+ 7.4      7.5
...
+ 7.0      7.0
+ 4.2.0+   6.7.1

2. AGP 与 Android Studio 的版本对应关系
AS版本                              支持AGP版本
Narwhal 4 Feature Drop | 2025.1.4  4.0-8.13
Narwhal 3 Feature Drop | 2025.1.3  4.0-8.13
Narwhal Feature Drop | 2025.1.2	   4.0-8.12
Narwhal | 2025.1.1	               3.2-8.11
Meerkat Feature Drop | 2024.3.2	   3.2-8.10 #当前版本 2024.3.2 Patch 1
Meerkat | 2024.3.1	               3.2-8.9
Ladybug Feature Drop | 2024.2.2	   3.2-8.8

3. CMake版本对应
关系：AGP → 调用 CMake → 调用 NDK → 生成 libxxx.so
AGP版本   推荐CMake版本 NDK     说明
+ 8.6+     3.30.3     27~28   最新版本，并行性能最佳 #当前选择3.30.3
+ 7.4~8.5  3.22.1     23~25   长期支持版
+ 7.0~7.4  3.18.1     21~23   稳定版，兼容旧模块

4. NDK版本与C++版本对应
NDK版本	 支持的C++标准	        
r27   C++20 稳定 / C++23 部分实现
r26   C++20 全面支持 / 实验性 C++23
r25b  C++17 / 大部分 C++20
r24   C++17 完整 / C++20 改进
r23b  C++17 完整 / C++20 部分支持   
r22b  C++17 / 部分 C++20
r21e  C++17 / 实验性 C++20




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