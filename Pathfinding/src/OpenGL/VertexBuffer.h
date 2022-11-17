#ifndef VertexBuffer_CLASS_H
#define VertexBuffer_CLASS_H

#include <glad/glad.h>
#include "GLErrorCheck.h"

class VertexBuffer
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	template<typename T>
	VertexBuffer(T* vertices, GLsizeiptr size)
	{
		GLCall(glGenBuffers(1, &ID));
		Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	}

	~VertexBuffer();

	template<typename T>
	void ChangeData(T* vertices, GLsizeiptr size)
	{
		Bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
		Unbind();
	}

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
};

#endif