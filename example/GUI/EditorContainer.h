#pragma once
#include "..\Engine\Container.h"

#include "..\Config.h"

class EditorContainer : public Container {

	void onUpdate() override
	{
		ImGui::Begin("Settings", nullptr);

			ImGui::InputInt("Counts", &Config::i_sides, 1, 10);
			if (Config::i_sides <= 2)
				Config::i_sides = 3;

			ImGui::InputFloat("Radius", &Config::f_size, 1, 10);
			if (Config::i_sides <= 1)
				Config::i_sides = 2;

			ImGui::ColorEdit4("Background", Config::color_bg, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("Circle Color", Config::color_circle, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs);

		ImGui::End();
	}
};