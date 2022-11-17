#pragma once
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shaders/Shaders.h"
#include <GLFW/glfw3.h>
#include "Mono/Mono.h"
#include "Mono/CommonData/Vectors.h"

//Defines the bounds (top-left corner and bottom-right corner) of the square
struct SquareBounds
{
	Vectors::Vector2 Pos1;
	Vectors::Vector2 Pos2;
};

struct Point
{
	int X;
	int Y;
};

class Grid
{
private:
	//Every square location (boundaries) are stored here in 2x glm::vec2
	SquareBounds* SquareLocations;
	//Every square's color
	Vector3* SquareColors;
	VertexBuffer* ColorBuffer;
	//Amount of squares in a row
	int SquareCountPerRow;
	//Normalized square width and height in float
	float NormalizedUnit;
	//Saves the locations of every individual square and places them in SquareLocations
	void SaveSquareLocations(Vectors::Vector2* original, Vectors::Vector2* offsets);
public:
	int TotalSquares;


	Grid(int squareCount);
	~Grid();

	//Creates the base square, that will be copied. It is optional to use this method, using a manually made array is fine as well.
	void GenerateBaseSquareArray(Vectors::Vector2(&squares)[4], float spacing = 0.01f);
	//Returns array with square cords. that fills the canvas. Call delete[] on returned array !
	Vectors::Vector2* GenerateOffsetArray(Vectors::Vector2* baseSquare);
	//
	void GenerateColorsArray(Vector3 color);
	//Returns the clicked square
	int GetSquareByPosition(double mouseX, double mouseY);

	VertexArray GenerateGrid(Vectors::Vector3 squareColors = Vectors::Vector3(0.4f, 0.1f, 1.0f));

	void ChangeSquareColor(int square, Vector3 color);

	//Converts one dimension square location to two
	Point ConvertToPoint(int square);
};

