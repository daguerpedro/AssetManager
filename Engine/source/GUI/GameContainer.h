#pragma once
#include "..\Generic\Container.h"

#include <Engine.h>

class GameContainer : public Container {
public:
	sf::RenderTexture rt{};
	sf::Vector2u lastSize{ 0, 0 };

	GameContainer()
	{
		rt.create(0, 0);
	}
	void onUpdate(const float& dt) override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::Begin("Game view", nullptr);
			
		ImVec2 size = ImGui::GetContentRegionAvail();
		sf::Vector2u newSize(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
		if (newSize != lastSize) {
			if (!rt.create(newSize.x, newSize.y)) {	}
			lastSize = newSize;
		}

		sf::Color c= sf::Color::Black;

		if (Engine::GetInstance()->sceneHandler.active != nullptr)
			c = Conversion::floatToColor(Engine::GetInstance()->sceneHandler.active->backColor);

		rt.clear(c);
			

		ImGui::Image(rt);

		ImGui::End();
		ImGui::PopStyleVar();		
	}
};