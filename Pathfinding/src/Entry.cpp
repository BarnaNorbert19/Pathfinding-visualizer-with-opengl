#pragma once

#include "GLFWSteps.h"
#include "Mono/Mono.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

int SuqareCount = 30;

static void PrintAssemblyTypes(MonoAssembly* assembly)
{
	MonoImage* image = mono_assembly_get_image(assembly);
	const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
	int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

	for (int32_t i = 0; i < numTypes; i++)
	{
		uint32_t cols[MONO_TYPEDEF_SIZE];
		mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

		const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
		const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

		printf("%s.%s\n", nameSpace, name);
	}
}


int main(void)
{
	GLFWwindow* window = GLFWSteps::CreateWindow("Test");

	if (window == nullptr)
		return -1;

	Mono mono = Mono();
	auto test = mono.LoadCSharpAssembly("PathfindingAlgorithms/bin/Debug/PathfindingAlgorithms.dll");
	auto testInstance = mono.InstantiateClass(test, "PathfindingAlgorithms", "Pathfinding");
	mono.CallMethod(testInstance);

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