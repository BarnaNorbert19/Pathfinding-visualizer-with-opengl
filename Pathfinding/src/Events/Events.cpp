#include "Events.h"

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

		int square = args->GridObj->GetSquareByPosition(normalizedX, normalizedY);
		Point test = args->GridObj->ConvertToPoint(square);

		MonoAssembly* csharpAssembly = args->MonoObj->LoadCSharpAssembly("PathfindingAlgorithms/bin/Debug/PathfindingAlgorithms.dll");
		MonoObject* insta = args->MonoObj->InstantiateClass(csharpAssembly, "PathfindingAlgorithms", "Events");
		Vector3 color = args->MonoObj->CallMethod<Vector3>(insta, "OnSquareClicked");

		args->GridObj->ChangeSquareColor(square, glm::vec3(color.Pos1, color.Pos2, color.Pos3));
	}
}
