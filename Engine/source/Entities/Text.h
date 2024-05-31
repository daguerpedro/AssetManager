#pragma once
#include "../Generic/Entity.h"

class Text : public Entity
{
public:
	sf::Text primitive;

	Text(const unsigned int& layer, const std::string& text, const sf::Font& font, unsigned int charSize)
		: Entity(layer) {

		primitive = sf::Text(text, font, charSize);

		drawAble = &primitive;
		transformable = &primitive;
	}

	void OnUpdate(const int& dt) override {

	}

	void onPreUpdate() override {
		
	};

	void OnPostUpdate() override {

	};

};