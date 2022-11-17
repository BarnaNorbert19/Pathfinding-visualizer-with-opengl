#include "VertexArray.h"
#include "GLErrorCheck.h"

// Constructor that generates a Vertex Array ID
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &ID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1, &ID));
}

// Binds the Vertex Array
void VertexArray::Bind()
{
	GLCall(glBindVertexArray(ID));
}

// Unbinds the Vertex Array
void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}