#pragma once
#include <glad/glad.h>
#include <iostream>
#include "OpenGL/VertexArray.h"
#include "Grid.h"

class GLFWSteps
{
public:
	static GLFWwindow* WindowPointer;
	static void CreateWindow(const char* title = "Default", int windowWidth = 960, int windowHeight = 720);
	static void WindowLoop(VertexArray* vao, Grid* grid);
	static void CleanUp();
};