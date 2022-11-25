#pragma once
#include "GLFWSteps.h"
#include "Mono/Mono.h"
#include "Grid.h"
#include <GLFW/glfw3.h>
#include "Events/Events.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720
#define SQUARE_COUNT 30

int main(void)
{
	GLFWSteps::CreateWindow("Test");

	if (GLFWSteps::WindowPointer == nullptr)
		return -1;

	Mono mono = Mono("vendor/mono/lib", "\\vendor", "PathfindingAlgorithms");
	mono.LoadCSharpAssembly("PathfindingAlgorithms/bin/Debug/PathfindingAlgorithms.dll");
	
	ImGuiInit imgui = ImGuiInit();
	

	{
		Grid grid = Grid(SQUARE_COUNT);
		VertexArray vao = grid.GenerateGrid();

		SquareClickEventArgs args =
		{
			&grid,
			&mono
		};

		glfwSetWindowUserPointer(GLFWSteps::WindowPointer, &args);
		glfwSetMouseButtonCallback(GLFWSteps::WindowPointer, Events::OnSquareClick);

		GLFWSteps::WindowLoop(&vao, &grid, &imgui);
	}

	GLFWSteps::CleanUp();

	return 0;
}