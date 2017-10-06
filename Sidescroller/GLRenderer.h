#pragma once
#include <SDL.h>
#include "GLHeaders.h"
#include <iostream>


class GLRenderer {
public:
    void init();

private:
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);

};