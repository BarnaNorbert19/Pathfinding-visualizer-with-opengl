#include "Grid.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shaders/Shaders.h"
#include "GLFWSteps.h"


void Grid::SaveSquareLocations(Vectors::Vector2* original, Vectors::Vector2* offsets)
{
	SquareLocations = new SquareBounds[TotalSquares];

	for (int i = 0; i < TotalSquares; i++)
	{
		SquareBounds temp;

		temp.Pos1 = original[0] + offsets[i];
		temp.Pos2 = original[2] + offsets[i];

		SquareLocations[i] = temp;
	}
}

Grid::Grid(int squareCount, float slideTopBy)
{
	SlideTopBy = 2.0f / slideTopBy / 2.0f;
	SquareCountPerRow = squareCount;
	NormalizedUnitX = 2.0f / squareCount;
	NormalizedUnitY = (2.0f - SlideTopBy) / squareCount;
	TotalSquares = squareCount * squareCount;
	ColorBuffer = NULL;
	SquareColors = NULL;
	SquareLocations = NULL;
}

Grid::~Grid()
{
	delete[] SquareLocations;
	delete[] SquareColors;
	delete ColorBuffer;
}

void Grid::GenerateBaseSquareArray(Vectors::Vector2(&squares)[4], float spacing)
{
	const float x = - 1.0f + NormalizedUnitX;
	const float y = 1.0f - NormalizedUnitY;

	squares[0] = Vectors::Vector2(- 1.0f + spacing, 1.0f - SlideTopBy - spacing);
	squares[1] = Vectors::Vector2(- 1.0f + spacing, y - SlideTopBy);
	squares[2] = Vectors::Vector2(x, y - SlideTopBy);
	squares[3] = Vectors::Vector2(x, 1.0f - SlideTopBy - spacing);
}

Vectors::Vector2* Grid::GenerateOffsetArray(Vectors::Vector2* baseSquare)
{
	Vectors::Vector2* squares = new Vectors::Vector2[TotalSquares];
	Vectors::Vector2 temp = Vectors::Vector2(0.0f, 0.0f);
	squares[0] = temp;

	for (int i = 1; i < (TotalSquares); i++)
	{
		if (i % SquareCountPerRow == 0)
		{
			temp.Y -= NormalizedUnitY;
			temp.X = 0.0f;

			squares[i] = temp;
		}

		else
		{

			temp.X += NormalizedUnitX;
			squares[i] = temp;
		}
	}

	SaveSquareLocations(baseSquare, squares);

	return squares;
}

void Grid::GenerateColorsArray(Vectors::Vector3 color)
{
	SquareColors = new Vectors::Vector3[TotalSquares];

	for (int i = 0; i < TotalSquares; i++)
	{
		SquareColors[i] = color;
	}
}

int Grid::GetSquareByPosition(double mouseX, double mouseY)
{
	for (int i = 0; i < TotalSquares; i++)
	{
		if (SquareLocations[i].Pos1.X <= mouseX && SquareLocations[i].Pos2.X >= mouseX
			&& SquareLocations[i].Pos1.Y >= mouseY && SquareLocations[i].Pos2.Y <= mouseY)
		{
			return i;
		}
	}

	return -1;
}

VertexArray Grid::GenerateGrid(Vectors::Vector3 squareColors)
{
	Vectors::Vector2 vertices[4];
	GenerateBaseSquareArray(vertices);

	GLuint indices[] =
	{
		0, 1, 2, 2, 0, 3
	};

	VertexArray vao;
	vao.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	auto vbo = VertexBuffer(vertices, sizeof(vertices));

	// Links VBO to VAO
	vao.LinkVertexBuffer(vbo, 0, 2, 0);

	Vectors::Vector2* offsets = GenerateOffsetArray(vertices);

	GenerateColorsArray(Vectors::Vector3(0.4f, 0.2f, 0.4f));

	VertexBuffer offsetBuffer(offsets, TotalSquares * sizeof(Vectors::Vector2));


	vao.LinkVertexBuffer(offsetBuffer, 1, 2, 0);//size = how many dimension we have && stride = data slices
	glVertexAttribDivisor(1, 1);

	ColorBuffer = new VertexBuffer(SquareColors, TotalSquares * sizeof(Vectors::Vector3));
	vao.LinkVertexBuffer(*ColorBuffer, 2, 3, 0);//size = how many dimension we have && stride = data slices
	glVertexAttribDivisor(2, 1);

	// Generates Index Buffer Object and links it to indices
	IndexBuffer ibo(indices, sizeof(vertices));

	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
	ibo.Unbind();
	offsetBuffer.Unbind();
	ColorBuffer->Unbind();

	ShaderSource ss = Shaders::ParseShader("src/OpenGL/Shaders/Squares.glsl");
	GLuint shader = Shaders::CreateShader(ss.VertexSource, ss.FragmentSource);
	Shaders::Activate(shader);

	delete[] offsets;

	return vao;
}

void Grid::ChangeSquareColor(int square, Vectors::Vector3 color)
{
	SquareColors[square] = color;
}

void Grid::ReDrawSquarePixels()
{
	ColorBuffer->ChangeData(SquareColors, TotalSquares * sizeof(Vectors::Vector3));
}



Point Grid::ConvertIntToPoint(int square)
{
	Point p;
	p.X = square % SquareCountPerRow;
	p.Y = square / SquareCountPerRow;

	return p;
}

int Grid::ConvertPointToInt(Point square)
{
	return (square.Y * SquareCountPerRow + square.X);
}