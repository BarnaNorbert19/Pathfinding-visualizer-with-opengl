#pragma once

class ImGuiInit
{
public:
	ImGuiInit();
	~ImGuiInit();

	void CreateFrame();
	void Render();
	float MenuBarHeight();

private:
	void SetupMenuBar();
};

