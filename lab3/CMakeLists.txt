cmake_minimum_required(VERSION 3.10)
project(OpenCV_Lab3)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} src)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab3 ${SOURCES})

target_link_libraries(lab3 ${OpenCV_LIBS})