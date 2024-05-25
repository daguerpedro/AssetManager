#pragma once
#include "../Generic/Entity.h"

class Test : public Entity	
{
	sf::CircleShape circle;
public:
	sf::Color color;

	// Make position and other things here, so it can be manipulated via IMGUI

	Test(const unsigned int& layer, sf::Color c, unsigned int radius, unsigned int sides)
		: Entity(layer), color(c) {
		circle = sf::CircleShape(radius, sides);
		circle.setFillColor(c);
		circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
		drawAble = &circle;
		transformable = &circle;
	}

	void OnUpdate(const int& dt) override {
		auto& p = Engine::GetInstance()->rtarget->getView().getCenter();
		circle.setPosition(p);
	}
};