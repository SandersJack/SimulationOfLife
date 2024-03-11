cmake_minimum_required(VERSION 3.20)
project(SimulationOfLife)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/WorldObjects/include)

# Add subdirectories
add_subdirectory(WorldObjects)

# Add your source files
add_executable(SoL 
  SimLife.cc
  src/SimManager.cc
  src/WObject.cc
  src/World.cc
)

# Link libraries
target_link_libraries(SoL WorldObjects)
