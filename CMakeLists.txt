cmake_minimum_required(VERSION 3.16)
project(MyRaylibProject)

set(CMAKE_CXX_STANDARD 17)

# Path to your external raylib directory
set(RAYLIB_DIR "$ENV{HOME}/raylib")

# Add raylib as a subdirectory (this builds it along with your project)
add_subdirectory(${RAYLIB_DIR} ${CMAKE_BINARY_DIR}/raylib_build)

# Add your executable - main is inside src/
add_executable(MyRaylibProject src/main.cpp
        src/test.cpp
        src/leaderboard.cpp
        src/leaderboard.h
        src/tcpServerSide.cpp
        src/tcpClientSide.cpp)

# Link raylib
target_link_libraries(MyRaylibProject raylib)

# Include raylib headers
target_include_directories(MyRaylibProject PRIVATE ${RAYLIB_DIR}/src)
