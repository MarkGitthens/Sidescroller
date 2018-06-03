cmake_minimum_required(VERSION 3.5.0)
project(Sidescroller)

include(src/CMakeLists.txt)

if(MSVC)
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
endif()

if(UNIX)
    find_package (SDL2 REQUIRED)
    find_package (SDL2_image)

    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(sidescroller ${SDL2_LIBRARIES})
    endif()

    if(SDL2_IMAGE_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(sidescroller ${SDL2_IMAGE_LIBRARIES})
    endif()
endif()

install(TARGETS sidescroller DESTINATION bin/)
