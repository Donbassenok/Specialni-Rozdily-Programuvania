cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(src)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab3 ${SOURCES})

target_link_libraries(lab3 ${OpenCV_LIBS} Threads::Threads)