
# CMAKE的最低版本。可以低于gradle中指定的版本，例如: 3.22.1 3.18.1, 3.10.2
cmake_minimum_required(VERSION 3.18.1)
# 工程名称，工程初始化点
project(myLib)

# 获取目录下所有CPP的文件
# GLOB 当前目录; GLOB_RECURSE 包含子目录
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_BASE "${CMAKE_CURRENT_SOURCE_DIR}/base/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS_ANDROID "${CMAKE_CURRENT_SOURCE_DIR}/utils_android/*.cpp")

# 添加动态库，指定库名称、类型、相对路径
add_library(
        demo
        SHARED
        ${SOURCE_CPP_FILES_OF_BASE}
        ${SOURCE_CPP_FILES_OF_TEST}
        ${SOURCE_CPP_FILES_OF_UTILS}
        ${SOURCE_CPP_FILES_OF_UTILS_ANDROID}
        main.cpp
)

# 为目标指定头文件路径
#PRIVATE：私有。仅当前目标使用，依赖此目标的其他目标看不到这些头文件路径
#PUBLIC：公共。当前目标使用，依赖此目标的其他目标也能看到这些头文件路径
#INTERFACE：接口。当前目标不使用，依赖此目标的其他目标能看到这些头文件路径
target_include_directories(demo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/include/
)

# 添加预编译的库，指定预编译的库的路径
# ffmpeg
add_library(avcodec SHARED IMPORTED)
add_library(avfilter SHARED IMPORTED)
add_library(avformat SHARED IMPORTED)
add_library(avutil SHARED IMPORTED)
add_library(swresample SHARED IMPORTED)
add_library(swscale SHARED IMPORTED)

set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libavcodec.so)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libavfilter.so)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libavformat.so)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libavutil.so)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libswresample.so)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/ffmpeg/libs/${ANDROID_ABI}/libswscale.so)

# 链接库
target_link_libraries(
        demo
        avcodec #ffmpeg
        avfilter
        avformat
        avutil
        swresample
        swscale

        z
        android
        log
)