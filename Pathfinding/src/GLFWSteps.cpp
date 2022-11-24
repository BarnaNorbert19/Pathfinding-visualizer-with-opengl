#include "GLFWSteps.h"

GLFWwindow* GLFWSteps::WindowPointer = nullptr;

void GLFWSteps::CreateWindow(const char* title, int windowWidth, int windowHeight)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Error ! " << "Could not initalize GLFW !" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    WindowPointer = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    if (!WindowPointer)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        CleanUp();
        return;
    }
    printf("GLFW loaded, version: %s\n", glfwGetVersionString());
    /* Make the window's context current */
    glfwMakeContextCurrent(WindowPointer);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status != 1)
    {
        std::cout << "Failed to load GLAD" << std::endl;
        CleanUp();
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
}

void GLFWSteps::WindowLoop(VertexArray* vao, Grid* grid)
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(WindowPointer))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        vao->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, grid->TotalSquares);


        /* Swap front and back buffers */
        glfwSwapBuffers(WindowPointer);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void GLFWSteps::CleanUp()
{
    // Delete window before ending the program
    glfwDestroyWindow(WindowPointer);
    glfwTerminate();
}
