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
	GLFWSteps::CreateWindow("Pathfinding", SCREEN_WIDTH, SCREEN_HEIGHT);

	if (GLFWSteps::WindowPointer == nullptr)
		return -1;

	Mono mono = Mono("vendor/mono/lib", "\\vendor", "PathfindingAlgorithms");
	mono.LoadCSharpAssembly("bin/Debug-windows-x86_64/PathfindingAlgorithms/PathfindingAlgorithms.dll");
	
	ImGuiInit imgui = ImGuiInit();
	imgui.CreateFrame();
	float height = imgui.MenuBarHeight();

	{
		Grid grid = Grid(SQUARE_COUNT, height);
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

	//GLFWSteps::CleanUp(); this line is called in imgui destructor, calling it before imgui cleanup raises an error

	return 0;
}