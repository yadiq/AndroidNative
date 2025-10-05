LOCAL_PATH := $(call my-dir) #设置当前模块的编译路径为当前文件夹路径

include $(CLEAR_VARS) #清理(可能由其他模块设置过的)编译环境中用到的变量

LOCAL_MODULE := Test #当前模块的名称

LOCAL_SRC_FILES := test1.c #当前模块包含的源代码文件
LOCAL_SRC_FILES += test2.cpp
LOCAL_SRC_FILES += test3.c

# for logging
LOCAL_LDLIBS    := -llog
# for native windows
# for native asset manager
LOCAL_LDLIBS    += -landroid

#not allowed with 'C++'
# LOCAL_CFLAGS    += -std=c99
#not allowed with 'C'
# LOCAL_CFLAGS    += -std=c++11 -Wall -UNDEBUG

include $(BUILD_SHARED_LIBRARY) #编译共享库




