
# CMAKE的最低版本
cmake_minimum_required(VERSION 3.4.1)

# 获取目录下所有CPP的文件
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_PARENT "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS_ANDROID "${CMAKE_CURRENT_SOURCE_DIR}/utils_android/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS_OPENSSL "${CMAKE_CURRENT_SOURCE_DIR}/utils_openssl/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_JSONCPP "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/jsoncpp/*.inl")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_TEST_CURL "${CMAKE_CURRENT_SOURCE_DIR}/test_curl/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_TEST_TYPE "${CMAKE_CURRENT_SOURCE_DIR}/test_type/*.cpp")

# 指定头文件路径
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/${ANDROID_ABI}/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/curl/include/
)

# 添加动态库，指定库名称、类型、相对路径
add_library(
        demo
        SHARED
        ${SOURCE_CPP_FILES_OF_PARENT}
        ${SOURCE_CPP_FILES_OF_UTILS}
        ${SOURCE_CPP_FILES_OF_UTILS_ANDROID}
        ${SOURCE_CPP_FILES_OF_UTILS_OPENSSL}
        ${SOURCE_CPP_FILES_OF_JSONCPP}
        ${SOURCE_CPP_FILES_OF_TEST}
        ${SOURCE_CPP_FILES_OF_TEST_CURL}
        ${SOURCE_CPP_FILES_OF_TEST_TYPE}
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
        demo
        crypto
        ssl
        curl #curl依赖于zlib和openssl
        z
        android
        log
)