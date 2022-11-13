#include "VertexBuffer.h"
#include "GLErrorCheck.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(glm::vec2* vertices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(glm::vec3* vertices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &ID));
}

void VertexBuffer::ChangeData(glm::vec3* vertices, GLsizeiptr size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	Unbind();
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