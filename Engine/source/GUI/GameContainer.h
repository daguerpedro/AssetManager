#pragma once
#include "..\Generic\Container.h"
#include "Config.h"

#include <Engine.h>

class GameContainer : public Container {
public:
	sf::RenderTexture rt{};
	sf::Vector2u lastSize{ 0, 0 };

	GameContainer()
	{
		rt.create(0, 0);
	}
	void onUpdate(const int& dt) override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

		ImGui::Begin("Game view", nullptr);
			
		ImVec2 size = ImGui::GetContentRegionAvail();
		sf::Vector2u newSize(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
		if (newSize != lastSize) {
			if (!rt.create(newSize.x, newSize.y)) {	}
			lastSize = newSize;
		}

			rt.clear({
				static_cast<uint8_t>(Config::color_bg[0] * 255),
				static_cast<uint8_t>(Config::color_bg[1] * 255),
				static_cast<uint8_t>(Config::color_bg[2] * 255),
				static_cast<uint8_t>(Config::color_bg[3] * 255)
			});
			
			Engine::GetInstance()->entityHandler.updateEntities(dt);

			ImGui::Image(rt);
		ImGui::End();
		ImGui::PopStyleVar();		
	}
};