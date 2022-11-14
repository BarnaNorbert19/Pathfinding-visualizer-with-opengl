#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

class Mono
{
private:
	char* ReadBytes(const std::string& filepath, uint32_t* outSize);
	MonoDomain* RootDomain;
	MonoDomain* AppDomain;
public:
	Mono();
	~Mono();

	MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);
	void PrintAssemblyTypes(MonoAssembly* assembly);
	MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);
	MonoObject* InstantiateClass(MonoAssembly* assembly, const char* namespaceName, const char* className);
	void CallMethod(MonoObject* objectInstance);
	void CallMethod(MonoObject* objectInstance, float value);
};

