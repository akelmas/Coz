cmake_minimum_required(VERSION 3.7)


project(Coz)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Coz_SOURCE_DIR}/cmake")
set(BIN_DIR ${Coz_SOURCE_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (MSVC)
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})



add_executable(Coz src/main.cpp src/graphics.cpp src/coz.cpp src/controller.cpp src/gamelogic.cpp)


target_link_libraries(Coz ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})
install(TARGETS Coz RUNTIME DESTINATION ${BIN_DIR})


