cmake_minimum_required(VERSION 3.5)
project(Ray_Tracing_Animation)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)

#add all source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

#add all header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glm)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)
include_directories(/usr/local/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} glfw3 pthread X11 GL Xrandr Xi dl assimp)