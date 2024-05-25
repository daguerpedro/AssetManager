#pragma once
#include "..\Generic\Container.h"

#include "Config.h"
#include <Engine.h>
#include <Entities/Test.h>

class EditorContainer : public Container 
{
	float c[4]{ 0,0,1,1 };
	
	int sides = 3;
	int radius = 25;

	void onUpdate(const int& dt) override
	{		
			ImGui::Begin("Settings", nullptr);
			ImGui::ColorEdit4("Background", Config::color_bg, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs);
			ImGui::Separator();

            if (ImGui::TreeNode("Entity List"))
            {
				int i = 0;

				for (auto e : Engine::GetInstance()->entityHandler.entities)
				{
					i++;

					if (ImGui::Button(("Delete##" + std::to_string(i)).c_str()))
					{
						Engine::GetInstance()->entityHandler.remove(e);
					}

	                ImGui::Separator();
				}

                ImGui::TreePop();
            } 
			if (ImGui::TreeNode("Entity Creator"))
			{
				const char* items[] = { "Test" };
				static int item_current_idx = 0;

				const char* combo_preview_value = items[item_current_idx];

				if (ImGui::BeginCombo("Type", combo_preview_value))
				{
					for (int n = 0; n < IM_ARRAYSIZE(items); n++)
					{
						const bool is_selected = (item_current_idx == n);
						if (ImGui::Selectable(items[n], is_selected))
							item_current_idx = n;
												
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				ImGui::ColorEdit4("Color", c);
				ImGui::InputInt("Sides", &sides, 1, 1);
				ImGui::InputInt("Radius", &radius, 1, 1);

				if (sides <= 2) sides = 3;


				if (ImGui::Button("Create"))
				{
					Engine::GetInstance()->entityHandler.pushEntity(std::make_shared<Test>(1, sf::Color{
						static_cast<sf::Uint8>(c[0] * 255),
						static_cast<sf::Uint8>(c[1] * 255),
						static_cast<sf::Uint8>(c[2] * 255),
						static_cast<sf::Uint8>(c[3] * 255)
						}, radius, sides));

					std::string text = "Criado entity do tipo ";
					text += items[item_current_idx];
					text += " Raio: ";
					text += std::to_string(radius);

					Engine::console.log(text);
				}
				ImGui::TreePop();
			}


			ImGui::ShowDemoWindow();

		ImGui::End();
	}
};