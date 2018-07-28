[![Build Status](https://semaphoreci.com/api/v1/maelstromdrift/sidescroller/branches/master/badge.svg)](https://semaphoreci.com/maelstromdrift/sidescroller)
# Sidescroller
This is a sample project being used to learn more about creating a custom 2d game engine using SDL2 and then eventually openGL.
# Requirments
- CMake
- SDL2 
- SDL2_image
- SDL2_mixer

# Generate Build Files
# Windows
- Extract and copy the include and lib directories from SDL2 and it's extension libraries into dependencies/SDL2
- Navigate to project root
- Create a folder named build/
- Navigate into newly created build/ directory.
- From command prompt run cmake ..

# Ubuntu 
- Navigate to project root
- install cmake version 3.5.0+

- Once you have CMake 3.5+ installed enter the following commands in the terminal

- mkdir build
- cd build
- sudo apt-get update
- sudo apt-get install libsdl2-dev
- sudo apt-get install libsdl2-image-dev
- sudo apt-get install libsdl2-mixer-dev
- cmake ..
