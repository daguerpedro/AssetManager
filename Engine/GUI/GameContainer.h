#pragma once
#include "..\Container.h"
#include "Config.h"

class GameContainer : public Container {
public:
	sf::RenderTexture rt{};
	sf::Vector2u lastSize{ 0, 0 };

	GameContainer()
	{
		rt.create(0, 0);
	}
	void onUpdate() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::SetNextWindowPos({ 0,0 });

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
			
			//TODO: Render Entity from entity manager
			sf::CircleShape shape{Config::f_size, (size_t)Config::i_sides};

			shape.setFillColor({
				static_cast<uint8_t>(Config::color_circle[0] * 255),
				static_cast<uint8_t>(Config::color_circle[1] * 255),
				static_cast<uint8_t>(Config::color_circle[2] * 255),
				static_cast<uint8_t>(Config::color_circle[3] * 255)
				});

			shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2 );
			shape.setPosition(rt.getView().getCenter());
			rt.draw(shape);

			ImGui::Image(rt);
		ImGui::End();
		ImGui::PopStyleVar();		
	}
};