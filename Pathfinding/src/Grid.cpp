#include "Grid.h"



void Grid::SaveSquareLocations(glm::vec2* original, glm::vec2* offsets)
{
	SquareLocations = new SquareBounds[TotalSquares];

	for (int i = 0; i < TotalSquares; i++)
	{
		SquareBounds temp;

		temp.pos1 = original[0] + offsets[i];
		temp.pos2 = original[2] + offsets[i];

		SquareLocations[i] = temp;
	}
}

Grid::Grid(int squareCount)
{
	SquareCountPerRow = squareCount;
	NormalizedUnit = 2.0f / squareCount;
	TotalSquares = squareCount * squareCount;
}

Grid::~Grid()
{
	delete[] SquareLocations;
	delete[] SquareColors;
	delete ColorBuffer;
}

void Grid::GenerateBaseSquareArray(glm::vec2(&squares)[4], float spacing)
{
	const float x = -1.0f + NormalizedUnit;
	const float y = 1.0f - NormalizedUnit;

	squares[0] = glm::vec2(-1.0f + spacing, 1.0f - spacing);
	squares[1] = glm::vec2(-1.0f + spacing, y);
	squares[2] = glm::vec2(x, y);
	squares[3] = glm::vec2(x, 1.0f - spacing);
}

glm::vec2* Grid::GenerateOffsetArray(glm::vec2* baseSquare)
{
	glm::vec2* squares = new glm::vec2[TotalSquares];
	glm::vec2 temp = glm::vec2(0.0f, 0.0f);
	squares[0] = temp;

	for (int i = 1; i < (TotalSquares); i++)
	{
		if (i % SquareCountPerRow == 0)
		{
			temp.y -= NormalizedUnit;
			temp.x = 0.0f;

			squares[i] = temp;
		}

		else
		{

			temp.x += NormalizedUnit;
			squares[i] = temp;
		}
	}

	SaveSquareLocations(baseSquare, squares);

	return squares;
}

void Grid::GenerateColorsArray(glm::vec3 color)
{
	SquareColors = new glm::vec3[TotalSquares];

	for (int i = 0; i < TotalSquares; i++)
	{
		SquareColors[i] = color;
	}
}

int Grid::GetSquareByPosition(double mouseX, double mouseY)
{
	for (int i = 0; i < TotalSquares; i++)
	{
		if (SquareLocations[i].pos1.x <= mouseX && SquareLocations[i].pos2.x >= mouseX
			&& SquareLocations[i].pos1.y >= mouseY && SquareLocations[i].pos2.y <= mouseY)
		{
			return i;
		}
	}

	return -1;
}

void Grid::OnSquareClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		double normalizedX = -1.0 + 2.0 * xPos / width;
		double normalizedY = 1.0 - 2.0 * yPos / height;

		int square = GetSquareByPosition(normalizedX, normalizedY);

		ChangeSquareColor(square, glm::vec3(0.2f, 1.0f, 0.1f));
	}
}

VertexArray Grid::GenerateGrid(glm::vec3 squareColors)
{
	glm::vec2 vertices[4];
	GenerateBaseSquareArray(vertices);

	GLuint indices[] =
	{
		0, 1, 2, 2, 0, 3
	};

	VertexArray vao;
	vao.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VertexBuffer<glm::vec2> vbo(vertices, sizeof(vertices));

	// Links VBO to VAO
	vao.LinkVertexBuffer<glm::vec2>(vbo, 0, 2, 0);

	glm::vec2* offsets = GenerateOffsetArray(vertices);

	GenerateColorsArray(glm::vec3(0.4, 0.2, 0.4));

	VertexBuffer<glm::vec2> offsetBuffer(offsets, TotalSquares * sizeof(glm::vec2));

	vao.LinkVertexBuffer<glm::vec2>(offsetBuffer, 1, 2, 0);//size = how many dimension we have && stride = data slices
	glVertexAttribDivisor(1, 1);

	ColorBuffer = new VertexBuffer<glm::vec3>(SquareColors, TotalSquares * sizeof(glm::vec3));
	vao.LinkVertexBuffer<glm::vec3>(*ColorBuffer, 2, 3, 0);//size = how many dimension we have && stride = data slices
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

void Grid::ChangeSquareColor(int square, glm::vec3 color)
{
	if (square >= 0)//prevent heap overflow, sometimes picks up value -1
	{
		SquareColors[square] = color;
		ColorBuffer->ChangeData(SquareColors, TotalSquares * sizeof(glm::vec3));
	}
}