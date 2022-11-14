#include "VertexBuffer.h"
#include "GLErrorCheck.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices

template<class T>
VertexBuffer<T>::VertexBuffer(T* vertices, GLsizeiptr size)
{
	GLCall(glGenBuffers(1, &ID));
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

template<class T>
VertexBuffer<T>::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &ID));
}

template<class T>
void VertexBuffer<T>::ChangeData(T* vertices, GLsizeiptr size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	Unbind();
}

template<class T>
// Binds the VBO
void VertexBuffer<T>::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

template<class T>
// Unbinds the VBO
void VertexBuffer<T>::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}