cmake_minimum_required(VERSION 3.10)

project(LowLevelFileManip VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/inventory.cpp)

add_executable(llfm ${SOURCES})
target_include_directories(llfm PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")