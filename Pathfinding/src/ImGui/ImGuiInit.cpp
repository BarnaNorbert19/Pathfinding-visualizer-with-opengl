#include "ImGuiInit.h"
#include "../GLFWSteps.h"
#include "imgui_impl_glfw.h"
#include <imgui.h>
#include "imgui_impl_opengl3.h"

ImGuiInit::ImGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(GLFWSteps::WindowPointer, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");
}

ImGuiInit::~ImGuiInit()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiInit::CreateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	SetupMenuBar();
	ImGui::EndFrame();
}

void ImGuiInit::Render()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(GLFWSteps::WindowPointer, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImGuiInit::SetupMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Clear")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) 
			{
				GLFWSteps::CleanUp();
				std::exit(0);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

