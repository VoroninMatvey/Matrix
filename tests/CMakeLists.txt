cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 23)
project("generator")

set(SRCS src/generator.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC "include")