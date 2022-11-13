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

// Links a Vertex Buffer to the Vertex Array using a certain layout
void VertexArray::LinkVertexBuffer(VertexBuffer& vbo, GLuint layout, GLuint size, GLsizei stride)
{
	vbo.Bind();
	GLCall(glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (void*)0));
	GLCall(glEnableVertexAttribArray(layout));
	vbo.Unbind();
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