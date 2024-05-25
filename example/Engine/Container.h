#pragma once

#include <imgui.h>

class Container
{
public:
	virtual void onUpdate() { 
		ImGui::Begin("Container", nullptr);
		ImGui::End();
	};
};