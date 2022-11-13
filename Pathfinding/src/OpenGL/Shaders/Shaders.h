#pragma once

#include <iostream>
#include <glad/glad.h>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shaders
{
private:
	static GLuint CompileShader(GLuint type, const std::string& source);
public:
	static ShaderSource ParseShader(const std::string& path);
	static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static void Activate(GLuint shader);
	static void Delete(GLuint shader);
};

