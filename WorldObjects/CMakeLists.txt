# Set sources
file(GLOB SOURCES "src/*.cc")

# Add headers if necessary
include_directories(include)

# Add library
add_library(WorldObjects ${SOURCES})

# Link dependencies if needed
target_link_libraries(WorldObjects)

