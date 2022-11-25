#include "Mono.h"
#include "../Events/Events.h"
#include <fstream>
#include <iostream>
#include <filesystem>


char* Mono::ReadBytes(const std::string& filepath, uint32_t* outSize)
{
	std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

	if (!stream)
	{
		// Failed to open the file
		std::cout << "Error ! File not found file: " << filepath << std::endl;
		return nullptr;
	}

	std::streampos end = stream.tellg();
	stream.seekg(0, std::ios::beg);
	uint32_t size = end - stream.tellg();

	if (size == 0)
	{
		// File is empty
		std::cout << "Error ! File is empty: " << filepath << std::endl;
		return nullptr;
	}

	char* buffer = new char[size];
	stream.read((char*)buffer, size);
	stream.close();

	*outSize = size;
	return buffer;
}

void Mono::LoadInternalCalls()
{
	mono_add_internal_call("PathfindingAlgorithms.CommonData.ExternalCalls::ChangeColor", &Events::ChangeColor);
	mono_add_internal_call("PathfindingAlgorithms.CommonData.ExternalCalls::ReDraw", &Events::ReDraw);
	mono_add_internal_call("PathfindingAlgorithms.CommonData.ExternalCalls::ResetGrid", &Events::ResetGrid);
}

Mono::Mono(const char* monoAssemblyPath, const char* monoDirsPath, const char* appDomainName, char* configuration)
{
	mono_set_assemblies_path(monoAssemblyPath);

	std::string curPath = std::filesystem::current_path().string();
	curPath.append(monoDirsPath);
	const char* assembly = curPath.c_str();

	mono_set_dirs(assembly, ".");

	RootDomain = mono_jit_init(appDomainName);
	if (RootDomain == nullptr)
	{
		std::cout << "Error ! Could not initalize JIT" << std::endl;
		return;
	}

	// Create an App Domain
	char* appDomain = _strdup(appDomainName);
	AppDomain = mono_domain_create_appdomain(appDomain, configuration);
	mono_domain_set(AppDomain, true);
	LoadInternalCalls();
}

Mono::~Mono()
{
	if (AppAssembly)
		mono_assembly_close(AppAssembly);
	/*if (AppDomain)
		mono_domain_free(AppDomain, true);*/
	if (RootDomain)
		mono_domain_free(RootDomain, true);

}

void Mono::LoadCSharpAssembly(const std::string& assemblyPath)
{
	std::string fullPath = std::filesystem::current_path().parent_path().string() + "\\" + assemblyPath;

	uint32_t fileSize = 0;
	char* fileData = ReadBytes(fullPath, &fileSize);

	// NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
	MonoImageOpenStatus status;
	MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

	if (status != MONO_IMAGE_OK)
	{
		const char* errorMessage = mono_image_strerror(status);
		std::cout << "Error ! While loading Mono assembly error message: " << errorMessage << std::endl;
		return;
	}

	AppAssembly = mono_assembly_load_from_full(image, fullPath.c_str(), &status, 0);
	mono_image_close(image);

	// Don't forget to free the file data
	delete[] fileData;
}

MonoClass* Mono::GetClassInAssembly(const char* namespaceName, const char* className)
{
	MonoImage* image = mono_assembly_get_image(AppAssembly);
	MonoClass* klass = mono_class_from_name(image, namespaceName, className);

	if (klass == nullptr)
	{
		std::cout << "Error ! Could not find class: " << std::endl;
		return nullptr;
	}

	return klass;

}

MonoObject* Mono::InstantiateClass(const char* namespaceName, const char* className)
{
	// Get a reference to the class we want to instantiate
	MonoClass* klass = GetClassInAssembly(namespaceName, className);

	// Allocate an instance of our class
	MonoObject* classInstance = mono_object_new(AppDomain, klass);

	if (classInstance == nullptr)
	{
		std::cout << "Error ! Could not Instantiate class " << className << std::endl;
		return nullptr;
	}

	// Call the parameterless (default) constructor
	mono_runtime_object_init(classInstance);
	
	return classInstance;
}


