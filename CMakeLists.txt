cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 23)
project("determination")

set(SRCS src/Matrix.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC "include")

option(INT_MATRIX "use an integer for the matrix" OFF)
if(INT_MATRIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE INT_MATRIX)
endif()

add_subdirectory(tests)