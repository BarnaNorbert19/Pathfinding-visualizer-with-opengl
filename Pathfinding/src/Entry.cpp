#pragma once

#include "GLFWSteps.h"
#include "Mono/Mono.h"
#include "Events/Events.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

int SuqareCount = 30;


int main(void)
{
	GLFWwindow* window = GLFWSteps::CreateWindow("Test");

	if (window == nullptr)
		return -1;

	Mono mono = Mono();

	{
		Grid grid = Grid(SuqareCount);
		VertexArray vao = grid.GenerateGrid();

		SquareClickEventArgs args =
		{
			&grid,
			&mono
		};

		glfwSetWindowUserPointer(window, &args);
		glfwSetMouseButtonCallback(window, Events::OnSquareClick);

		GLFWSteps::WindowLoop(window, &vao, &grid);
	}
	GLFWSteps::CleanUp(window);

	return 0;
}