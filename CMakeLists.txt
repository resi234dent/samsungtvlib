cmake_minimum_required(VERSION 3.19)
project(samsungtvlib)

set(OPENSSL_SOURCE_DIR /usr/local/opt/openssl@1.1/lib)
set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/local/Cellar/boost/1.76.0/include" "/usr/local/Cellar/boost/1.76.0/lib" "/usr/local/opt/openssl@1.1/include"
        "/usr/local/opt/openssl@1.1/lib" "/usr/local/opt/openssl@1.1/lib/pkgconfig")
add_executable(samsungtvlib main.cpp ClientSocket.h ClientSocket.cpp)

target_link_libraries(samsungtvlib "${OPENSSL_SOURCE_DIR}/libssl.dylib"
        "${OPENSSL_SOURCE_DIR}/libcrypto.dylib" "/usr/local/Cellar/boost/1.76.0/lib/libboost_program_options.dylib")