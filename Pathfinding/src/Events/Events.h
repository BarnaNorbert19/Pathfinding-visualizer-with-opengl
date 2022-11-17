#pragma once
#include <glad/glad.h>
#include "../Mono/Mono.h"
#include "../Grid.h"

struct SquareClickEventArgs
{
	Grid* GridObj;
	Mono* MonoObj;
};

class Events
{
public:
	static void OnSquareClick(GLFWwindow* window, int button, int action, int mods);
	
};

