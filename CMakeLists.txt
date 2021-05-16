cmake_minimum_required(VERSION 3.0)

project(mutual_auth_rest)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${PROJECT_NAME} main.cpp)
    
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)


