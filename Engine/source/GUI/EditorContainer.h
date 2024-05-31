#pragma once
#include "..\Generic\Container.h"

#include "Config.h"
#include <Engine.h>
#include <Entities/Circle.h>

class EditorContainer : public Container 
{
	float col[4] = { 1, 0, 0, 1 };
	float rad = 5;
	int sid = 5;

	void onUpdate(const int& dt) override
	{		
		ImGui::Begin("Settings", nullptr);
			if (ImGui::TreeNode("Entity Creator"))
			{
				const char* items[] = { "Circulo" };
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

				ImGui::ColorEdit4("Color", col);
				ImGui::InputInt("Sides", &sid, 1, 1);
				ImGui::InputFloat("Radius", &rad, 1, 1);

				if (sid <= 2) sid = 3;

				if (ImGui::Button("Create"))
				{
					Engine::GetInstance()->globalEntityHandler.pushEntity(std::make_shared<Circle>(1, col, rad, sid));

					std::string text = "Criado entity do tipo ";
					text += items[item_current_idx];

					Engine::console.log(text);
				}
				ImGui::TreePop();
			}

			ImGui::ColorEdit4("Background", Config::color_bg, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs);
		ImGui::End();

		ImGui::Begin("Entites");
			if (ImGui::TreeNode("Entity List"))
			{
				Engine::console.log("[EDITORCONTAINER.H LINE 60] TODO: LIST SCENE ENTITES AND SCENE LIST.");
				int i = 0;

				for (auto e : Engine::GetInstance()->globalEntityHandler.entities)
				{
					i++;

					ImGui::SeparatorText("Orientation");

					ImGui::Text("Position"); ImGui::SameLine();
					ImGui::InputFloat2(("##P" + std::to_string(i)).c_str(), e->position, "%.f");

					ImGui::Text("Rotation"); ImGui::SameLine();
					ImGui::InputFloat(("##Rt" + std::to_string(i)).c_str(), &e->rotation);

					ImGui::Text("Scale"); ImGui::SameLine();
					ImGui::InputFloat2(("##S" + std::to_string(i)).c_str(), e->scale);

					ImGui::SeparatorText("Visual");

					ImGui::Text("Layer: %i", e->getLayer());
					ImGui::InputInt(("##L" + std::to_string(i)).c_str(), &e->Layer);

					if (std::shared_ptr<Circle> circle = dynamic_pointer_cast<Circle>(e))
					{
						ImGui::Text("Radius"); ImGui::SameLine();
						ImGui::InputFloat(("##Rd" + std::to_string(i)).c_str(), &circle->radius);

						ImGui::Text("Color"); ImGui::SameLine();
						ImGui::ColorEdit4(("##Clr" + std::to_string(i)).c_str(), circle->color);
					}

					ImGui::SeparatorText("Other");

					if (ImGui::Button(("Delete##" + std::to_string(i)).c_str()))
					{
						Engine::GetInstance()->globalEntityHandler.remove(e);
					}

					ImGui::Separator();
				}

				ImGui::TreePop();
			}
		ImGui::End();
	}
};