cmake_minimum_required(VERSION 3.16)
project(llvm-project)

#set(CMAKE_CXX_FLAGS "-std=c++17")
#set(CMAKE_CXX_COMPILER g++-9)
set(EXECUTABLE_OUTPUT_PATH build)
set(LIBRARY_OUTPUT_PATH build)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#include_directories(core/lib)

add_executable(launcher main.cpp point.cpp)