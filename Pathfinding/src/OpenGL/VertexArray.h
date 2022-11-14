#ifndef VertexArray_CLASS_H
#define VertexArray_CLASS_H

#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray
{
private:
	// ID reference for the Vertex Array Object
	GLuint ID;
public:


	// Constructor that generates a VAO ID
	VertexArray();
	~VertexArray();

	// Links a VBO to the VAO using a certain layout
	template<typename T>
	void LinkVertexBuffer(VertexBuffer<T>& vbo, GLuint layout, GLuint size, GLsizei stride);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
};
#endif