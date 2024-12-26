
# CMAKE的最低版本
cmake_minimum_required(VERSION 3.4.1)

# 获取目录下所有CPP的文件
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_PARENT "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_CPPTEST_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/cpp_test/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_JSONCPP "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.inl")

# 指定头文件路径
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/${ANDROID_ABI}/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/curl/include/
#        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/
)

# 添加动态库，指定库名称、类型、相对路径
add_library(
        test
        SHARED
        ${SOURCE_CPP_FILES_OF_PARENT}
        ${SOURCE_CPP_FILES_OF_UTILS}
        ${SOURCE_CPP_FILES_OF_CPPTEST_UTILS}
        ${SOURCE_CPP_FILES_OF_JSONCPP}
)

# 添加预编译的库，指定预编译的库的路径
add_library(crypto
        SHARED
        IMPORTED)
set_target_properties(crypto
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/libs/${ANDROID_ABI}/libcrypto.so
)

add_library(ssl
        SHARED
        IMPORTED)
set_target_properties(ssl
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/libs/${ANDROID_ABI}/libssl.so
)

add_library(curl
        STATIC
        IMPORTED)
set_target_properties(curl
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/curl/libs/${ANDROID_ABI}/libcurl.a
)

# 链接库
target_link_libraries(
        test
        crypto
        ssl
        curl #curl依赖于zlib和openssl
        z
        android
        log
)