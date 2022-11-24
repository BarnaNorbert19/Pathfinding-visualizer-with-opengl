#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "CommonData/Point.h"

class Mono
{
private:
	char* ReadBytes(const std::string& filepath, uint32_t* outSize);
	MonoDomain* RootDomain = nullptr;
	MonoDomain* AppDomain = nullptr;
	MonoAssembly* AppAssembly = nullptr;
	void LoadInternalCalls();

public:
	Mono(const char* monoAssemblyPath, const char* monoDirsPath, const char* appDomainName, char* configuration = nullptr);
	~Mono();

	void LoadCSharpAssembly(const std::string& assemblyPath);
	MonoClass* GetClassInAssembly(const char* namespaceName, const char* className);
	MonoObject* InstantiateClass(const char* namespaceName, const char* className);

	template <typename... Vars>
	void CallMethod(MonoObject* objectInstance, const char* methodName, Vars... param)
	{
		const int paramCount = sizeof...(Vars);

		MonoClass* instanceClass = mono_object_get_class(objectInstance);

		MonoMethod* method = mono_class_get_method_from_name(instanceClass, methodName, paramCount);

		if (!method)
		{
			std::cout << "Error ! Could not find method" << std::endl;
			return;
		}

		void* paramArray[paramCount] = { &param... };

		MonoObject* exception;
		mono_runtime_invoke(method, instanceClass, paramArray, &exception);

		if (exception)
		{
			mono_unhandled_exception(exception);
		}
	}
};

