include_directories(include)

file(GLOB SRC "src/*.cc")
file(GLOB INC "include/*.hh")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(WorldObjects SHARED ${SRC})