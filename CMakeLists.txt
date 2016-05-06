cmake_minimum_required (VERSION 3.5)
#set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
set(CMAKE_CXX_FLAGS "-std=c++1z")

project(zenplugin)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

find_program(CLDOC cldoc)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(lib)
