#pragma once

class ImGuiInit
{
public:
	ImGuiInit();
	~ImGuiInit();

	void CreateFrame();
	void Render();

private:
	void SetupMenuBar();
};

