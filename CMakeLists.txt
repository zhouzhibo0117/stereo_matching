cmake_minimum_required(VERSION 3.10)
project(stereopsis)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(stereopsis
        src/main.cpp
        src/image_io.cpp
        src/include/image_io.h
        src/matching_methods.cpp
        src/include/matching_methods.h
        src/error_analysis.cpp
        src/include/error_analysis.h
        src/basic_image_processing.cpp
        src/include/basic_image_processing.h)

target_link_libraries( stereopsis ${OpenCV_LIBS} )