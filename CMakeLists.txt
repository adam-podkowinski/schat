cmake_minimum_required(VERSION 3.16.0)
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
set(CMAKE_BUILD_TYPE Debug)

include_directories(include/)

find_package (Threads)
find_package(Boost 1.75.0 COMPONENTS filesystem unit_test_framework)

add_executable(schat ${SRC_FILES})
add_executable(test_schat tests/test.cpp)

target_link_libraries(schat Threads::Threads)
target_precompile_headers(schat PUBLIC include/precompiled.h)

target_link_libraries(test_schat
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
