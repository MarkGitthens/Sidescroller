cmake_minimum_required(VERSION 3.5.0)
project(Sidescroller)

include(src/CMakeLists.txt)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(CMAKE_CXX_STANDARD 11)

add_executable(sidescroller ${VULTURE2D_SRC})

if(MSVC)
    set(SDL2_DIR dependencies/SDL2)
    set(SDL2_INCLUDE dependencies/SDL2/include)
    set(SDL2_LIB ../dependencies/SDL2/lib)

    include_directories(${SDL2_INCLUDE})

    target_link_libraries(sidescroller
            ${SDL2_LIB}/x86/SDL2
            ${SDL2_LIB}/x86/SDL2main
            ${SDL2_LIB}/x86/SDL2_image)

    #TODO: check to see if we are creating a 32 or 64 bit msvc project
    #if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64") 
        #target_link_libraries(sidescroller ${SDL2_LIB}/x64/*)        
    #endif()
endif()

if(UNIX)
    find_package (SDL2 REQUIRED)
    find_package (SDL2_image REQUIRED)

    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS})
        target_link_libraries(sidescroller ${SDL2_LIBRARIES})
    endif()

    if(SDL2_IMAGE_FOUND)
        include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
        target_link_libraries(sidescroller ${SDL2_IMAGE_LIBRARIES})
    endif()
endif()

install(TARGETS sidescroller DESTINATION bin/)