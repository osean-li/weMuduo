cmake_minimum_required(VERSION 3.10.2)
project(weMuduo)

# cmake => makefile   make
# weMuduo最终编译成so动态库，设置动态库的路径，放在根目录的lib文件夹下面
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置调试信息 以及 启动C++11语言标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")

# 定义参与编译的源代码文件 
aux_source_directory(. SRC_LIST)
# 编译生成动态库mymuduo
add_library(weMuduo SHARED ${SRC_LIST} Poller.cpp Poller.h DefaultPoller.cpp EPollPoller.cpp EPollPoller.h CurrentThread.cpp CurrentThread.h)