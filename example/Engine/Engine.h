#pragma once
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "GuiHandler.h"

class Engine
{
	sf::RenderWindow window;
	ImGuiIO* io;

	   
public:
	GuiHandler guiHandler;

	Engine();
	 ~Engine();

    void init(ImVec2 winsize, const std::string& title);
};