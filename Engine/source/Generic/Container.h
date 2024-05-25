#pragma once

#include <imgui.h>
#include <SFML/Graphics.hpp>

class Container
{
public:
	virtual void onUpdate(const int& dt) {
		ImGui::Begin("Container", nullptr);
		ImGui::End();
	};
};