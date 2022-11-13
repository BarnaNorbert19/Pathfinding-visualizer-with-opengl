#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OpenGL/VertexArray.h"
#include "Grid.h"

class GLFWSteps
{
public:
	static GLFWwindow* CreateWindow(const char* title = "Default", int windowWidth = 960, int windowHeight = 720);
	static void WindowLoop(GLFWwindow* window, VertexArray* vao, Grid* grid);
	static void CleanUp(GLFWwindow*);
};