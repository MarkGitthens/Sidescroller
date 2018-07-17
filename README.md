[![Build Status](https://semaphoreci.com/api/v1/maelstromdrift/sidescroller/branches/master/badge.svg)](https://semaphoreci.com/maelstromdrift/sidescroller)
# Sidescroller
This is a sample project being used to learn more about creating a custom 2d game engine using SDL2 and then eventually openGL.
# Requirments
-CMake

-SDL2 (tested with 2.0.8)

-SDL2_image (tested with 2.0.1)

# Generate Build Files
# Windows
- Extract SDL2 and SDL2_image include and lib directories into dependencies/SDL2
- Navigate to project root
- Create a folder named build/
- Navigate into newly created build/ directory.
- From command prompt run cmake ..

# Ubuntu 
- Navigate to project root
- install cmake version 3.5.0+
- mkdir build
- cd build
- sudo apt-get update
- sudo apt-get install libsdl2-dev
- sudo apt-get install libsdl2-image-dev
- cmake ..
