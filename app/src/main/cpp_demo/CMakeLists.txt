
# CMAKE的最低版本。可以低于gradle中指定的版本，例如: 3.22.1 3.18.1, 3.10.2
cmake_minimum_required(VERSION 3.18.1)

# 获取目录下所有CPP的文件
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_PARENT "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_BASE "${CMAKE_CURRENT_SOURCE_DIR}/base/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS_ANDROID "${CMAKE_CURRENT_SOURCE_DIR}/utils_android/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_UTILS_OPENSSL "${CMAKE_CURRENT_SOURCE_DIR}/utils_openssl/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_JSON "${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/json/json_utils/*.cpp")
file(GLOB_RECURSE SOURCE_CPP_FILES_OF_TEST "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

# 添加动态库，指定库名称、类型、相对路径
add_library(
        demo
        SHARED
        ${SOURCE_CPP_FILES_OF_PARENT}
        ${SOURCE_CPP_FILES_OF_BASE}
        ${SOURCE_CPP_FILES_OF_UTILS}
        ${SOURCE_CPP_FILES_OF_UTILS_ANDROID}
        ${SOURCE_CPP_FILES_OF_UTILS_OPENSSL}
        ${SOURCE_CPP_FILES_OF_JSON}
        ${SOURCE_CPP_FILES_OF_TEST}
)

# 为目标指定头文件路径
#PRIVATE：私有。仅当前目标使用，依赖此目标的其他目标看不到这些头文件路径
#PUBLIC：公共。当前目标使用，依赖此目标的其他目标也能看到这些头文件路径
#INTERFACE：接口。当前目标不使用，依赖此目标的其他目标能看到这些头文件路径
target_include_directories(demo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/openssl/include/${ANDROID_ABI}/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/curl/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/otherlibs/json/
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