#pragma once
#include "..\Generic\Container.h"

#include "..\..\etc\imgui\imgui_stdlib.h"

#include <Engine.h>
#include <Entities/Circle.h>
#include <Entities/Text.h>

class EditorContainer : public Container 
{
	std::shared_ptr<Entity> selected;

	static int resizeCallback(ImGuiInputTextCallbackData* data)
	{
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			ImVector<char>* my_str = (ImVector<char>*)data->UserData;
			IM_ASSERT(my_str->begin() == data->Buf);
			my_str->resize(data->BufSize);
			data->Buf = my_str->begin();

			Engine::GetInstance()->console.log("resizeCallback");
		}
		return 0;
	};

	void onUpdate(const float& dt) override
	{		
		ShowSceneDetails();
	}

	void ShowSceneDetails()
	{
		ImGui::Begin("Scene");
		auto handler = Engine::GetInstance()->sceneHandler;
		auto scene = handler.active;

		if (scene != nullptr)
		{			
			ImGui::SeparatorText("Info");
			ImGui::Text("%s Scene.", handler.activeName.c_str());
			ImGui::ColorEdit4("Back ground", scene->backColor, ImGuiColorEditFlags_NoInputs);

			ImGui::SeparatorText("Entities");
			if (ImGui::BeginListBox("##Entities", ImVec2(-FLT_MIN, (scene->sceneEntityHandler.entities.size() + 1) * ImGui::GetTextLineHeightWithSpacing())))
			{
				for (auto e : scene->sceneEntityHandler.entities)
				{
					const bool is_selected = (selected == e);
					if (ImGui::Selectable(e->name.c_str(), is_selected))
						selected = e;

					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();

				if (selected == nullptr && scene->sceneEntityHandler.entities.size() > 0)
					selected = scene->sceneEntityHandler.entities[0];
			}
		}
		ImGui::End();

		ImGui::Begin("Entity");

		if (scene != nullptr && selected != nullptr)
		{
			ImGui::Text("%s", selected->name.c_str());

			ImGui::Checkbox("Enabled", &selected->enabled);

			ImGui::InputInt("Layer", &selected->Layer, 1, 1);
			if (selected->Layer < 0)
				selected->Layer = 0;

			//todo: align
			ImGui::InputFloat2("Position", selected->position, "%.f");

			ImGui::InputFloat2("Scale", selected->scale, "%.f");

			ImGui::InputFloat("Rotation", &selected->rotation, 1, 1, "%.f");

			switch (selected->type)
			{
			case TEXT:
			{

				auto text = std::dynamic_pointer_cast<Text>(selected);
				ImGui::ColorEdit4("Color", text->color,ImGuiColorEditFlags_NoInputs);

				ImGui::InputText("Text", &text->text, ImGuiInputTextFlags_None, resizeCallback);
				ImGui::InputInt("Character Size", &text->charSize, 1, 1);
				break;
			}
			default:
				break;
			}

		}
		ImGui::End();
	}
};