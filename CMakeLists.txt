cmake_minimum_required(VERSION 3.20)

set(PROJECT SimulationOfLife)

project(${PROJECT})

file(GLOB SRC
     "src/*.cc")

set(MAIN_FILE SimLife.cc)
include_directories(include)

add_executable(${PROJECT} ${MAIN_FILE} ${SRC})