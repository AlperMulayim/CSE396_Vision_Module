project(HoughLines)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
cmake_minimum_required(VERSION 3.6)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "C:\\OpenCV\\mingw-build\\install")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:\\Users\\alper\\ClionProjects\\HoughLines")
add_executable(HoughLines main.cpp AlpPoint.cpp AlpPoint.h)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# linking
target_link_libraries(HoughLines ${OpenCV_LIBS})