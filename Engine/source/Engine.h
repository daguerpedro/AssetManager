#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "./Handlers/GuiHandler.h"
#include "./Handlers/EntityHandler.h"
#include "./Handlers/SceneHandler.h"
#include "./Utils/Conversion.h"
#include "./Utils/Console.h"


#include "imgui.h"
#include "imgui-SFML.h"

class Engine
{
private:
	bool started = false;
	void configStyle();
protected:
	ImGuiIO* io;

	Engine();
	 ~Engine();

	static Engine* _engine;
	
	sf::RenderWindow window;
public:
	sf::RenderTarget* renderTarget; 

	Engine(Engine& other) = delete; 
	void operator=(const Engine&) = delete;

	static Engine* GetInstance(); 
	static Console console;

    void init(bool enableEditor, ImVec2 winsize, const std::string& title);

	// Instance of the handlers.
	SceneHandler sceneHandler;
	EntityHandler globalEntityHandler; 
	GuiHandler guiHandler;

	std::function<void()> onStarted;
};