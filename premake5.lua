workspace "Pathfinding"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pathfinding"
    location "Pathfinding"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
    
    entrypoint "mainCRTStartup"

    staticruntime "off"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/GLAD-2.0/src/glad.c"
    }

    includedirs
    {
        "%{prj.name}/vendor/GLFW-3.3.8/include",
        "%{prj.name}/vendor/GLAD-2.0/include",
        "%{prj.name}/vendor/GLM-0.9.9.8/include",
        "%{prj.name}/vendor/mono/include"
    }
    
    libdirs 
    { 
        "%{prj.name}/vendor/GLFW-3.3.8/lib",
        "%{prj.name}/vendor/mono/lib"
    }

    links 
    { 
        "glfw3.lib", "opengl32.lib", "msvcrt.lib", "mono-2.0-sgen.lib"
    }
    

    filter "system:windows"
        cppdialect "C++20"
        cdialect "C17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            
        }

        postbuildcommands
        {
            "xcopy \"$(SolutionDir)Pathfinding\\vendor\\mono\\bin\\mono-2.0-sgen.dll\" \"$(TargetDir)\" /y"
        }

    filter {"system.windows", "configurations:Release"}
        buildoptions "/MT" --Multithreaded bcs of GLFW