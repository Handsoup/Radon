cmake_minimum_required(VERSION 3.5)

project(RadonTransform)

# Set the path to SFML directory
set(SFML_DIR "/home/peppermintlarry/SFML-2.6.1/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS audio REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(RadonTransform main.cpp RadIm.cpp CSVHandler.cpp InvRadIm.cpp FilterWheel.cpp)
target_link_libraries(RadonTransform ${OpenCV_LIBRARIES} sfml-audio)

