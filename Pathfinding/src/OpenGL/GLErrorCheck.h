#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();

bool GLCheckError(const char* function, const char* file, int line);