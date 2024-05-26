#pragma once
#include <SFML/Graphics.hpp>

#include "./Handlers/GuiHandler.h"
#include "./Handlers/EntityHandler.h"
#include "./Console.h"

#include "imgui.h"
#include "imgui-SFML.h"

class Engine
{
protected:
	ImGuiIO* io;

	Engine();
	 ~Engine();

	static Engine* _engine; // Singleton
	
	sf::RenderWindow window;
public:
	/// Its a primitive struct.
	/// Can be pointed as a window or a RenderTexture
	/// Window when its a release, RenderTexture when its a debug/editor.
	sf::RenderTarget* rtarget; 

	Engine(Engine& other) = delete; 
	void operator=(const Engine&) = delete;

	static Engine* GetInstance();  // Singleton access
	static Console console;

    void init(ImVec2 winsize, const std::string& title);

	// Instance of the handlers.
	EntityHandler entityHandler; 
	GuiHandler guiHandler;

};