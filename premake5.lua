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
        "%{prj.name}/vendor/GLAD-2.0/src/glad.c",
        "%{prj.name}/vendor/IMGUI-1.89.1/**.cpp",
        "%{prj.name}/vendor/IMGUI-1.89.1/**.h"
    }

    includedirs
    {
        "%{prj.name}/vendor/GLFW-3.3.8/include",
        "%{prj.name}/vendor/GLAD-2.0/include",
        "%{prj.name}/vendor/mono/include",
        "%{prj.name}/vendor/IMGUI-1.89.1"
    }
    
    libdirs 
    { 
        "%{prj.name}/vendor/GLFW-3.3.8/lib",
        "%{prj.name}/vendor/mono/lib"
    }

    links 
    { 
        "glfw3.lib", "opengl32.lib", "msvcrt.lib", "mono-2.0-sgen.lib", "eglib.lib", "libmono-static-sgen.lib", "MonoPosixHelper.lib"
    }

    staticruntime "on"
    runtime "Release"
    

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
            --"xcopy \"$(SolutionDir)Pathfinding\\vendor\\mono\\bin\\MonoPosixHelper.dll\" \"$(TargetDir)\" /y"
        }
    
    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"
    
    
project "PathfindingAlgorithms"
    location "PathfindingAlgorithms"
    kind "SharedLib"
    language "C#"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.cs"
    }

    links { "System.Drawing", "System" }