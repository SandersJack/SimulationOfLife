cmake_minimum_required(VERSION 3.20)

set(PROJECT SimulationOfLife)

project(${PROJECT})

file(GLOB SRC
     "src/*.cc")

set(MAIN_FILE SimLife.cc)
include_directories(include)

add_executable(${PROJECT} ${MAIN_FILE} ${SRC})

include_directories("WorldObjects/include")
target_link_libraries(${PROJECT_NAME} WorldObjects)
add_subdirectory(WorldObjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")