#ifndef IndexBuffer_CLASS_H
#define IndexBuffer_CLASS_H

#include <glad/glad.h>
#include "GLErrorCheck.h"

class IndexBuffer
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	IndexBuffer(GLuint* indices, GLsizeiptr size);
	~IndexBuffer();

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
};

#endif