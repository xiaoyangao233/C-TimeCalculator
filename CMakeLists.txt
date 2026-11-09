cmake_minimum_required(VERSION 3.20)
project(TimeCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Qt 的路径（本机绝对路径，换机器要改）
list(APPEND CMAKE_PREFIX_PATH "D:/Qt/6.8.3/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ===== 业务核心：两个界面共用 =====
add_library(TimeCore STATIC
    src/Time.cpp
    src/Date.cpp
    src/VideoRecord.cpp
    src/VideoStore.cpp
)
target_compile_options(TimeCore PRIVATE /utf-8)

# ===== 控制台版 =====
add_executable(TimeCalculator
    src/main.cpp
    src/ConsoleUI.cpp
    src/SelfTest.cpp
)
target_link_libraries(TimeCalculator PRIVATE TimeCore)
target_compile_options(TimeCalculator PRIVATE /utf-8)

# ===== Qt 版 =====
add_executable(TimeCalculatorQt
    src/QtMain.cpp
)
target_link_libraries(TimeCalculatorQt PRIVATE TimeCore Qt6::Widgets)
target_compile_options(TimeCalculatorQt PRIVATE /utf-8)