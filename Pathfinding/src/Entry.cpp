#pragma once

#include "GLFWSteps.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

int SuqareCount = 30;

int main(void)
{
	GLFWwindow* window = GLFWSteps::CreateWindow("Test");

	if (window == nullptr)
		return -1;

	{
		Grid grid = Grid(SuqareCount);
		VertexArray vao = grid.GenerateGrid();

		glfwSetWindowUserPointer(window, &grid);

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				if (Grid* grid = static_cast<Grid*>(glfwGetWindowUserPointer(window)))
				grid->OnSquareClick(window, button, action, mods);
			});

		GLFWSteps::WindowLoop(window, &vao, &grid);
	}
	GLFWSteps::CleanUp(window);

	return 0;
}