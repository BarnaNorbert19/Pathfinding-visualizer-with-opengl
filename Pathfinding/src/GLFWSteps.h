#pragma once
#include <glad/glad.h>
#include "OpenGL/VertexArray.h"
#include "ImGui/ImGuiInit.h"
#include <GLFW/glfw3.h>
#include "Grid.h"

class GLFWSteps
{
public:
	static GLFWwindow* WindowPointer;
	static void CreateWindow(const char* title = "Default", int windowWidth = 960, int windowHeight = 720);
	static void WindowLoop(VertexArray* vao, Grid* grid, ImGuiInit* imgui);
	static void CleanUp();
};