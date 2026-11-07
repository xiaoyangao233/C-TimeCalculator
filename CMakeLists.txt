#声明最低CMake版本
cmake_minimum_required(VERSION 3.20)

#声明项目名和语言
project(TimeCalculator LANGUAGES CXX)

#使用C++20，低于会报错
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#定义一个exe目标
add_executable(TimeCalculator 
	src/main.cpp
	src/Time.cpp
	src/Date.cpp
	src/VideoRecord.cpp
	src/SelfTest.cpp
	src/VideoStore.cpp
	src/ConsoleUI.cpp
)

#给目标加编译选项
target_compile_options(TimeCalculator PRIVATE /utf-8)
