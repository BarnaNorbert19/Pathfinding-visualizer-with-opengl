#pragma once
#include "Mono/CommonData/Vectors.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "Mono/CommonData/Point.h"

//Defines the bounds (top-left corner and bottom-right corner) of the square
struct SquareBounds
{
	Vectors::Vector2 Pos1;
	Vectors::Vector2 Pos2;
};

class Grid
{
private:
	//Every square location (boundaries) are stored here in 2x glm::vec2
	SquareBounds* SquareLocations;
	//Every square's color
	Vectors::Vector3* SquareColors;
	VertexBuffer* ColorBuffer;
	//Amount of squares in a row
	int SquareCountPerRow;
	//Normalized square width and height in float
	float NormalizedUnitX;
	float NormalizedUnitY;
	//Saves the locations of every individual square and places them in SquareLocations
	void SaveSquareLocations(Vectors::Vector2* original, Vectors::Vector2* offsets);
	//Creates the base square, that will be copied. It is optional to use this method, using a manually made array is fine as well.
	void GenerateBaseSquareArray(Vectors::Vector2(&squares)[4], float spacing = 0.009f);
	float SlideTopBy;
public:
	int TotalSquares;


	Grid(int squareCount, float slideTopBy);
	~Grid();

	//Returns array with square cords. that fills the canvas. Call delete[] on returned array !
	Vectors::Vector2* GenerateOffsetArray(Vectors::Vector2* baseSquare);
	//
	void GenerateColorsArray(Vectors::Vector3 color);
	//Returns the clicked square
	int GetSquareByPosition(double mouseX, double mouseY);

	VertexArray GenerateGrid(Vectors::Vector3 squareColors = Vectors::Vector3(0.4f, 0.1f, 1.0f));

	void ChangeSquareColor(int square, Vectors::Vector3 color);
	void ReDrawSquarePixels();

	//Converts one dimension square location to two
	Point ConvertIntToPoint(int square);

	int ConvertPointToInt(Point square);
};

