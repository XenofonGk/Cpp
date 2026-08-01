cmake_minimum_required(VERSION 3.20)
project(ArenaCore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All source files
add_executable(ArenaCore
    main.cpp
    src/input.cpp
    src/Character.cpp
    src/Warrior.cpp
    src/Mage.cpp
    src/Arena.cpp
)

# Tell compiler where to find headers
target_include_directories(ArenaCore PRIVATE include)

# Copy roster.txt to the build directory so the program can find it at runtime
configure_file(data/roster.txt ${CMAKE_BINARY_DIR}/roster.txt COPYONLY)