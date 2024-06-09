#pragma once

#include <imgui.h>
#include <SFML/Graphics.hpp>

class Container
{
public:
	virtual void onUpdate(const float& dt) {
		ImGui::Begin("Container", nullptr);
		ImGui::End();
	};
};