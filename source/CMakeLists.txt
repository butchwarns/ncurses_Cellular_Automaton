cmake_minimum_required (VERSION 3.20.2)
set (CMAKE_CXX_STANDARD 20)

# Set project name
project (ncurses_Cellular_Automaton)

# Find ncureses library and include its directory
find_package (Curses REQUIRED)
include_directories (${CURSES_INCLUDE_DIR})

# Add build target and specify source files for build
add_executable (${PROJECT_NAME} main.cpp Automaton.cpp Display.cpp Brain.cpp)

# Link ncurses library to the previously specified target
target_link_libraries (${PROJECT_NAME} ${CURSES_LIBRARIES})
