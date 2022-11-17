#include "VertexBuffer.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &ID));
}

// Binds the VBO
void VertexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

// Unbinds the VBO
void VertexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}