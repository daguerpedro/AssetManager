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
	char buff[255]{0};

	void onUpdate(const int& dt) override
	{		
		Settings();
		EntityCreator();
		EntityLister();
		ImGui::ShowStyleEditor();
	}

	void Settings()
	{
		ImGui::Begin("Settings", nullptr);		
			ImGui::ColorEdit4("Background", Config::color_bg, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoInputs);
		ImGui::End();
	};

	void EntityLister()
	{
		ImGui::Begin("Entites");

		for (auto e : Engine::GetInstance()->globalEntityHandler.entities)
			DisplayEntity(e);

		if (Engine::GetInstance()->sceneHandler.active != nullptr)
		for (auto e : Engine::GetInstance()->sceneHandler.active->sceneEntityHandler.entities)
			DisplayEntity(e);

		ImGui::End();
	};

	void DisplayEntity(std::shared_ptr<Entity> e)
	{
		auto ents = Engine::GetInstance()->globalEntityHandler.entities;
		int i = std::distance(ents.begin(), std::find(ents.begin(), ents.end(), e));

		//TODO: CHECK TYPE
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
			Engine::GetInstance()->sceneHandler.active->sceneEntityHandler.remove(e);
			Engine::GetInstance()->globalEntityHandler.remove(e);
		}

		ImGui::Separator();
	}

	void EntityCreator()
	{
		ImGui::Begin("Entity Creator");
		if (ImGui::TreeNode("Entity Creator"))
		{
			const char* items_type[] = { "Circle", "Text" };
			static int index_type = 0;

			const char* preview_type = items_type[index_type];

			if (ImGui::BeginCombo("Type", preview_type))
			{
				for (int n = 0; n < IM_ARRAYSIZE(items_type); n++)
				{
					const bool selected_type = (index_type == n);
					if (ImGui::Selectable(items_type[n], selected_type))
						index_type = n;

					if (selected_type)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			const char* items_loc[] = { "Global", "Scene" };
			static int index_loc = 0;

			const char* preview_loc = items_loc[index_loc];

			if (ImGui::BeginCombo("Location", preview_loc))
			{
				for (int n = 0; n < IM_ARRAYSIZE(items_loc); n++)
				{
					const bool selected_loc = (index_loc == n);
					if (ImGui::Selectable(items_loc[n], selected_loc))
						index_loc = n;

					if (selected_loc)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (index_type == 0)
			{
				ImGui::ColorEdit4("Color", col);
				ImGui::InputInt("Sides", &sid, 1, 1);
				ImGui::InputFloat("Radius", &rad, 1, 1);
			}
			if (index_type == 1)
			{
				ImGui::InputText("Text", buff, IM_ARRAYSIZE(buff));
			}
			if (sid <= 2) sid = 3;

			if (ImGui::Button("Create"))
			{
				EntityHandler* handler = &Engine::GetInstance()->globalEntityHandler;
				if (index_loc == 1)
					handler = &Engine::GetInstance()->sceneHandler.active->sceneEntityHandler;

				if (index_type == 0)
					handler->pushEntity(std::make_shared<Circle>(1, col, rad, sid));

				std::string text = "Criado entity do tipo ";
				text += items_type[index_type];
				text += " em ";
				text += items_loc[index_loc];

				Engine::console.log(text);
			}
			ImGui::TreePop();
		}
		ImGui::End();
	};

};