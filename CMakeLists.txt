cmake_minimum_required(VERSION 3.0.0)
project(myproject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(
  SRC_FILES
  src/main.cpp
)

include_directories(include/)

add_executable(myproject ${SRC_FILES})
