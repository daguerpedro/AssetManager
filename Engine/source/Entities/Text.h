#pragma once
#include "../Generic/Entity.h"

class Text : public Entity
{
public:
	sf::Text primitive;

	Text(const unsigned int& layer, const std::string& name, const std::string& text, const sf::Font& font, unsigned int charSize)
		: Entity(layer, name) {

		this->text = text;

		primitive = sf::Text(this->text, font, charSize);

		drawAble = &primitive;
		transformable = &primitive;

		type = TEXT;

		grabColors();
		
		
	}

	float color[4];

	std::string text;
	int charSize;

	void OnUpdate(const int& dt) override 
	{

	}

	void onPreUpdate() override {
		grabColors();

		text = primitive.getString();
		charSize = primitive.getCharacterSize();
	};

	void OnPostUpdate() override {
		primitive.setFillColor(Conversion::floatToColor(this->color));
		primitive.setString(text);
		
		charSize = charSize < 0 ? 0 : charSize;
		primitive.setCharacterSize(charSize);

		transformable->setOrigin(primitive.getLocalBounds().getSize().x / 2, primitive.getLocalBounds().getSize().y / 2);
	};

private:
	void grabColors()
	{
		color[0] = primitive.getFillColor().r / 255;
		color[1] = primitive.getFillColor().g / 255;
		color[2] = primitive.getFillColor().b / 255;
		color[3] = primitive.getFillColor().a / 255;
	}
};