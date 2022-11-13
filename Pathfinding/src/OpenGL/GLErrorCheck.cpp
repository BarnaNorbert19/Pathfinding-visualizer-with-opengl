#include "GLErrorCheck.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error (Begin)]" << std::endl
            << "Error code: " << error << std::endl
            << "Function: " << function << std::endl
            << "File: " << file << std::endl
            << "Line: " << line << std::endl
            << "[OpenGL Error (End)]" << std::endl;
        return false;
    }

    return true;
}
