#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

struct Vector3
{
	float Pos1;
	float Pos2;
	float Pos3;
};

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
	MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);
	MonoObject* InstantiateClass(MonoAssembly* assembly, const char* namespaceName, const char* className);
	template<typename T>
	T CallMethod(MonoObject* objectInstance, const char* methodName)
	{
		// Get the MonoClass pointer from the instance
		MonoClass* instanceClass = mono_object_get_class(objectInstance);

		// Get a reference to the method in the class
		MonoMethod* method = mono_class_get_method_from_name(instanceClass, methodName, 0);

		if (method == nullptr)
		{
			// No method called "PrintFloatVar" with 0 parameters in the class, log error or something
			T defaultValue;
			return defaultValue;
		}

		// Call the C# method on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		//with return value: 
		auto a = mono_runtime_invoke(method, objectInstance, nullptr, &exception);

		T returnValue = *(T*)mono_object_unbox(a);

		// TODO: Handle the exception

		return returnValue;
	}



	template <typename T>
	void CallMethod(MonoObject* objectInstance, const char* methodName, T value)
	{
		// Get the MonoClass pointer from the instance
		MonoClass* instanceClass = mono_object_get_class(objectInstance);

		// Get a reference to the method in the class
		MonoMethod* method = mono_class_get_method_from_name(instanceClass, methodName, 1);

		if (method == nullptr)
		{
			// No method called "IncrementFloatVar" with 1 parameter in the class, log error or something
			return;
		}

		// Call the C# method on the objectInstance instance, and get any potential exceptions
		MonoObject* exception = nullptr;
		void* param = &value;
		mono_runtime_invoke(method, objectInstance, &param, &exception);

		// TODO: Handle the exception
	}
};

