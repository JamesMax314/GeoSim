cmake_minimum_required(VERSION 3.12)
project(geoSim)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-variable") #-Wextra
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE debug)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Set the source files for your project
# Collect all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Collect all .h files in the src directory and its subdirectories
file(GLOB_RECURSE HEADER_FILES "src/*.h")

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Link GLFW and OpenGL libraries to your target
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL GLEW::GLEW)
