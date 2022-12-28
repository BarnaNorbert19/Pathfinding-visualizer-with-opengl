# Pathfinding

## Overview
Pathfinding visualizer, GUI made with OpenGL (GLFW, GLAD). The actual pathfinding algorithms are coded in C# from my previous project (with minor changes, since this project uses .NET framework). Scripting was made possible with Mono.
Really good opengl tutorial: https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

## Console
To remove Console edit premake5.lua -> kind "ConsoleApp" to kind "WindowedApp" or in VS Studio Linker->System->Subsystem and set it to Windows.

# Premake5
https://premake.github.io</br>Premake5 is project generator, very familiar to CMake (I just think it's better). Main difference is it uses LUA.

# GLFW
https://www.glfw.org</br>A OpenGL library, handles window creation and inputs.

# GLAD
https://glad.dav1d.de</br>Makes modern OpenGL usage possible.

# Mono
https://www.mono-project.com</br>.NET Framework C++ implementation.
