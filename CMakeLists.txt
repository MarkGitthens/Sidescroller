cmake_minimum_required(VERSION 3.5.0)
project(Sidescroller)

include(src/CMakeLists.txt)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(CMAKE_CXX_STANDARD 11)

add_executable(sidescroller ${VULTURE2D_SRC})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sidescroller)

foreach(source IN LISTS VULTURE2D_SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

if(MSVC)
    set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2)
    set(SDL2_INCLUDE ${SDL2_DIR}/include)
    set(SDL2_LIB ${SDL2_DIR}/lib)

    include_directories(${SDL2_INCLUDE})

    target_link_libraries(sidescroller
            ${SDL2_LIB}/x86/SDL2.lib
            ${SDL2_LIB}/x86/SDL2main.lib
            ${SDL2_LIB}/x86/SDL2_image.lib)

    #TODO: check to see if we are creating a 32 or 64 bit msvc project
    #if(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64") 
        #target_link_libraries(sidescroller ${SDL2_LIB}/x64/*)        
    #endif()

    ADD_CUSTOM_COMMAND (TARGET sidescroller POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/SDL2.dll            ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/SDL2_image.dll      ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/libjpeg-9.dll       ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/libpng16-16.dll     ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/libtiff-5.dll       ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/libwebp-7.dll       ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/zlib1.dll           ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/LICENSE.jpeg.txt    ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/LICENSE.png.txt     ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/LICENSE.tiff.txt    ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/LICENSE.webp.txt    ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB}/x86/LICENSE.zlib.txt    ${CMAKE_BINARY_DIR}/Debug ) 

    ADD_CUSTOM_COMMAND (TARGET sidescroller POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources  ${CMAKE_BINARY_DIR}/Debug/resources)   
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

ADD_CUSTOM_COMMAND (TARGET sidescroller POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources       ${CMAKE_BINARY_DIR}/resources )