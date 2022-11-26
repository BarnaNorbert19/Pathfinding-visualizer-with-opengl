#pragma once
#include "Events.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../Mono/CommonData/Point.h"

AlgoType Events::SelectedType = AlgoType::AStar;

void Events::OnSquareClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		double normalizedX = -1.0 + 2.0 * xPos / width;
		double normalizedY = 1.0 - 2.0 * yPos / height;

		SquareClickEventArgs* args = static_cast<SquareClickEventArgs*>(glfwGetWindowUserPointer(window));

		int square1d = args->GridObj->GetSquareByPosition(normalizedX, normalizedY);

		if (square1d == -1)
			return;

		Point square2d = args->GridObj->ConvertIntToPoint(square1d);
		
		bool shitState = false;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			shitState = true;
		}
		
		MonoObject* klass = args->MonoObj->InstantiateClass("PathfindingAlgorithms", "Events");
		args->MonoObj->CallMethod(klass, "OnSquareClicked", square2d, shitState, SelectedType);
	}

	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void Events::ChangeColor(Point square, Vectors::Vector3 color)
{
	SquareClickEventArgs* args = static_cast<SquareClickEventArgs*>(glfwGetWindowUserPointer(GLFWSteps::WindowPointer));
	
	int squareArrayPos = args->GridObj->ConvertPointToInt(square);
	args->GridObj->ChangeSquareColor(squareArrayPos, color);
}

void Events::ReDraw()
{
	SquareClickEventArgs* args = static_cast<SquareClickEventArgs*>(glfwGetWindowUserPointer(GLFWSteps::WindowPointer));

	args->GridObj->ReDrawSquarePixels();
}

void Events::ResetGrid()
{
	SquareClickEventArgs* args = static_cast<SquareClickEventArgs*>(glfwGetWindowUserPointer(GLFWSteps::WindowPointer));

	for (int i = 0; i < args->GridObj->TotalSquares; i++)
	{
		args->GridObj->ChangeSquareColor(i, Vectors::Vector3(0.4f, 0.2f, 0.4f));
	}

	args->GridObj->ReDrawSquarePixels();
}
