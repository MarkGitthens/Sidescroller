cmake_minimum_required(VERSION 3.8.2)

project(Sidescroller)

include(src/CMakeLists.txt)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin/)
set(SDL2_DIR dependencies/SDL2/)
set(SDL2_INCLUDE dependencies/SDL2/include)
set(SDL2_LIB dependencies/SDL2/lib)

include_directories(${SDL2_INCLUDE})

add_executable(sidescroller ${VULTURE2D_SRC})
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64") 
	target_link_libraries(sidescroller ${SDL2_LIB}/x64/*)
else()
	target_link_libraries(sidescroller ${SDL2_LIB}/x86/*)
endif()

install(TARGETS sidescroller DESTINATION bin/)