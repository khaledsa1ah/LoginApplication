cmake_minimum_required(VERSION 3.21)
project(Login_Application)

set(CMAKE_CXX_STANDARD 14)

add_executable(Login_Application "Login Application.cpp")

add_library(Library "Login Application library.cpp" "Login Application library.h")