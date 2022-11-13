#include "IndexBuffer.h"

// Constructor that generates a Index Buffer Object and links it to indices
IndexBuffer::IndexBuffer(GLuint* indices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &ID));
}

// Binds the IBO
void IndexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

// Unbinds the IBO
void IndexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}