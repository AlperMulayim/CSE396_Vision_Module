project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
cmake_minimum_required(VERSION 3.6)

set(OpenCV_DIR "C:\\OpenCV\\mingw-build\\install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:\\Users\\Hunter\\CLionProjects\\untitled")
add_executable(untitled main.cpp )

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)
target_link_libraries(untitled ${OpenCV_LIBS})