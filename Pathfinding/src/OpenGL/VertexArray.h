#ifndef VertexArray_CLASS_H
#define VertexArray_CLASS_H

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
	// Links a Vertex Buffer to the Vertex Array using a certain layout

	void LinkVertexBuffer(VertexBuffer& vbo, GLuint layout, GLuint size, GLsizei stride)
	{
		vbo.Bind();
		GLCall(glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (void*)0));
		GLCall(glEnableVertexAttribArray(layout));
		vbo.Unbind();
	}
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
};
#endif