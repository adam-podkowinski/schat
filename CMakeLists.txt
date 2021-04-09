cmake_minimum_required(VERSION 3.0.0)
project(schat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(
  SRC_FILES
  src/main.cpp
  src/networking/Client.cpp
  src/networking/Server.cpp
  src/SChat.cpp
)

include_directories(include/)

add_executable(schat ${SRC_FILES})
