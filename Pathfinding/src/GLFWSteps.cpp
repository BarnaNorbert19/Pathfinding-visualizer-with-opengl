#include "GLFWSteps.h"

GLFWwindow* GLFWSteps::CreateWindow(const char* title, int windowWidth, int windowHeight)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        CleanUp(window);
        return nullptr;
    }
    printf("GLFW loaded, version: %s\n", glfwGetVersionString());
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status != 1)
    {
        std::cout << "Failed to load GLAD" << std::endl;
        CleanUp(window);
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));


    return window;
}

void GLFWSteps::WindowLoop(GLFWwindow* window, VertexArray* vao, Grid* grid)
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        vao->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, grid->TotalSquares);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void GLFWSteps::CleanUp(GLFWwindow* window)
{
    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
}
