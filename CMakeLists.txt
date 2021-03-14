cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
project(Coz)
add_executable(Coz src/main.cpp src/graphics.cpp src/coz.cpp src/controller.cpp src/gamelogic.cpp)


target_include_directories(Coz PUBLIC /usr/local/include/SDL2/)
target_link_libraries(Coz /usr/local/lib/libSDL2.dylib)
target_link_libraries(Coz /usr/local/lib/libSDL2_image.dylib)
target_link_libraries(Coz /usr/local/lib/libSDL2_ttf.dylib)

