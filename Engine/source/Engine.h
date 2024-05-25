#pragma once
#include <SFML/Graphics.hpp>
#include "./Handlers/GuiHandler.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <Handlers/EntityHandler.h>

class Engine
{
protected:
	ImGuiIO* io;

	Engine();
	 ~Engine();

	static Engine* _engine;
	
	struct Console {
		std::vector<std::string> messages;

		void log(const std::string& m)
		{
			messages.push_back(m);
		}

		void clear()
		{
			messages.clear();
		}

		void draw()
		{
			ImGui::Begin("LOG");
			if (ImGui::SmallButton("Clear")) clear();

			if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -(ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing())), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NavFlattened))
			{
				for (auto s : messages)
					ImGui::TextUnformatted(s.c_str());
			}
			ImGui::EndChild();
			ImGui::End();
		}
	};
	
	sf::RenderWindow window;
public:
	sf::RenderTarget* rtarget;

	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;

	static Engine* GetInstance();
	static Console console;

    void init(ImVec2 winsize, const std::string& title);

	EntityHandler entityHandler;
	GuiHandler guiHandler;

};