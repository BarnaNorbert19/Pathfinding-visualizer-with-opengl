#include "Mono.h"

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

Mono::Mono()
{
	mono_set_assemblies_path("vendor/mono/lib");

	std::string curPath = std::filesystem::current_path().string();
	curPath.append("\\vendor");
	const char* assembly = curPath.c_str();

	mono_set_dirs(assembly, ".");

	MonoDomain* rootDomain = mono_jit_init("PathfindingScripting");
	if (rootDomain == nullptr)
	{
		// Maybe log some error here
		return;
	}

	// Store the root domain pointer
	RootDomain = rootDomain;

	// Create an App Domain
	char appDomain[21] = "PathfindingScripting";
	AppDomain = mono_domain_create_appdomain(appDomain, nullptr);
	mono_domain_set(AppDomain, true);
}

Mono::~Mono()
{
	if (RootDomain)
		mono_jit_cleanup(RootDomain);
}

MonoAssembly* Mono::LoadCSharpAssembly(const std::string& assemblyPath)
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
		return nullptr;
	}

	MonoAssembly* assembly = mono_assembly_load_from_full(image, fullPath.c_str(), &status, 0);
	mono_image_close(image);

	// Don't forget to free the file data
	delete[] fileData;

	return assembly;
}

MonoClass* Mono::GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className)
{
	MonoImage* image = mono_assembly_get_image(assembly);
	MonoClass* klass = mono_class_from_name(image, namespaceName, className);

	if (klass == nullptr)
	{
		std::cout << "Error ! Could not find class: " << std::endl;
		return nullptr;
	}

	return klass;

}

MonoObject* Mono::InstantiateClass(MonoAssembly* assembly, const char* namespaceName, const char* className)
{
	// Get a reference to the class we want to instantiate
	MonoClass* testingClass = GetClassInAssembly(assembly, namespaceName, className);

	// Allocate an instance of our class
	MonoObject* classInstance = mono_object_new(AppDomain, testingClass);

	if (classInstance == nullptr)
	{
		std::cout << "Error ! Could not Instantiate class " << className << std::endl;
		return nullptr;
	}

	// Call the parameterless (default) constructor
	mono_runtime_object_init(classInstance);

	return classInstance;
}