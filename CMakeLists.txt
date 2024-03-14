cmake_minimum_required(VERSION 3.20)
project(SimulationOfLife)

find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/WorldObjects/include)

# Add subdirectories
add_subdirectory(WorldObjects)

file(GLOB SOURCES src/*.cc)

# Add your source files
add_executable(SoL 
  SimLife.cc
  ${SOURCES}
)

# Link GLFW library to the executable
target_include_directories(SoL PRIVATE ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(SoL WorldObjects glfw)


