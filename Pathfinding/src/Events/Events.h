#pragma once
#include "../Mono/Mono.h"
#include "../Grid.h"
#include "../Mono/CommonData/Point.h"
#include "../GLFWSteps.h"

struct SquareClickEventArgs
{
	Grid* GridObj;
	Mono* MonoObj;
};

class Events
{
public:
	static void OnSquareClick(GLFWwindow* window, int button, int action, int mods);
	static void ChangeColor(Point square, Vectors::Vector3 color);//Internal call
	static void ReDraw();//Internal call
	static void ResetGrid();//Internal call
};

