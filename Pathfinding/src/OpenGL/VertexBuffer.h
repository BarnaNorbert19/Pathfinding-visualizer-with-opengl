#ifndef VertexBuffer_CLASS_H
#define VertexBuffer_CLASS_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include "GLErrorCheck.h"
#include <glm/vec3.hpp>

template <class T>
class VertexBuffer
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VertexBuffer(T* vertices, GLsizeiptr size);

	~VertexBuffer();


	void ChangeData(T* vertices, GLsizeiptr size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
};

#endif