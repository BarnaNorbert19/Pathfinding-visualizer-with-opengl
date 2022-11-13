#ifndef VertexBuffer_CLASS_H
#define VertexBuffer_CLASS_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include "GLErrorCheck.h"
#include <glm/vec3.hpp>

class VertexBuffer
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VertexBuffer(GLfloat* vertices, GLsizeiptr size);
	VertexBuffer(glm::vec2* vertices, GLsizeiptr size);
	VertexBuffer(glm::vec3* vertices, GLsizeiptr size);

	~VertexBuffer();


	void ChangeData(glm::vec3* vertices, GLsizeiptr size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
};

#endif