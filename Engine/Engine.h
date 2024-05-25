#pragma once
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "GuiHandler.h"

class Engine
{
protected:
	ImGuiIO* io;

	Engine();
	 ~Engine();

	 static Engine* _engine;
	  
public:
	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;

	static Engine* GetInstance();

	GuiHandler guiHandler;
	sf::RenderWindow window;

    void init(ImVec2 winsize, const std::string& title);
};