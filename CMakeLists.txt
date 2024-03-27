cmake_minimum_required(VERSION 3.20)
project(SimulationOfLife)

# Add GLTools submodule directory
#add_subdirectory(GLTools)

# Specify paths to the required frameworks on MacOS (assumes homebrew install)
set(glfw3_DIR, /opt/homebrew/opt/glfw/lib/cmake/glfw3)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

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

########################### GLTools ########################################
# Specify the relative path to the GLTools library build directory
set(LIBRARY_DIR GLTools/build)
# Link against the library
target_link_libraries(SoL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GLTools/build/libGLTools.a)
# Specify the relative include directory for GLTools library
target_include_directories(SoL PRIVATE GLTools/include)
############################# MathGL ########################################
target_include_directories(SoL PRIVATE GLTools/MathGL/include)
########################### Controls ########################################
# Specify the relative path to the Controls library build directory
target_include_directories(SoL PRIVATE GLTools/Controls/include)

# Link GLFW library to the executable
target_include_directories(SoL PRIVATE ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(SoL PRIVATE WorldObjects glfw -framework OpenGL GLEW::GLEW Freetype::Freetype)

