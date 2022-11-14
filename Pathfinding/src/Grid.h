#pragma once
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shaders/Shaders.h"
#include <GLFW/glfw3.h>

//Defines the bounds (top-left corner and bottom-right corner) of the square
struct SquareBounds
{
	glm::vec2 pos1;
	glm::vec2 pos2;
};

class Grid
{
private:
	//Every square location (boundaries) are stored here in 2x glm::vec2
	SquareBounds* SquareLocations;
	//Every square's color
	glm::vec3* SquareColors;
	VertexBuffer<glm::vec3>* ColorBuffer;
	//Amount of squares in a row
	int SquareCountPerRow;
	//Normalized square width and height in float
	float NormalizedUnit;
	//Saves the locations of every individual square and places them in SquareLocations
	void SaveSquareLocations(glm::vec2* original, glm::vec2* offsets);
public:
	int TotalSquares;


	Grid(int squareCount);
	~Grid();

	//Creates the base square, that will be copied. It is optional to use this method, using a manually made array is fine as well.
	void GenerateBaseSquareArray(glm::vec2(&squares)[4], float spacing = 0.01f);
	//Returns array with square cords. that fills the canvas. Call delete[] on returned array !
	glm::vec2* GenerateOffsetArray(glm::vec2* baseSquare);
	//
	void GenerateColorsArray(glm::vec3 color);
	//Returns the clicked square
	int GetSquareByPosition(double mouseX, double mouseY);
	void OnSquareClick(GLFWwindow* window, int button, int action, int mods);

	VertexArray GenerateGrid(glm::vec3 squareColors = glm::vec3(0.4f, 0.1f, 1.0f));

	void ChangeSquareColor(int square, glm::vec3 color);
};

