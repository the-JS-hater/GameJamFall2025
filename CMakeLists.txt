cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "*.cpp")
add_executable(game ${SOURCES})

target_include_directories(game PRIVATE "C:/raylib/raylib/src")
target_link_directories(game PRIVATE "C:/raylib/raylib/build/raylib/Release")
target_link_libraries(game PRIVATE raylib winmm gdi32 opengl32)
