#pragma once
#include "../Generic/Entity.h"

class Circle : public Entity
{
	sf::CircleShape circle;
public:
	float color[4] = { 1,1,1,1 };

	float radius = 2;

	Circle(const unsigned int& layer, float col[4], unsigned int radius = 5, unsigned int sides = 5)
		: Entity(layer), radius(radius) {
		color[0] = col[0];
		color[1] = col[1];
		color[2] = col[2];
		color[3] = col[3];

		circle = sf::CircleShape(radius, sides);
		circle.setFillColor(Conversion::floatToColor(col));
		circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
		drawAble = &circle;
		transformable = &circle;
	}

	void OnUpdate(const int& dt) override {

	}

	void onPreUpdate() override {
		radius = circle.getRadius();

		color[0] = (circle.getFillColor().r/255.f);
		color[1] = (circle.getFillColor().g/255.f);
		color[2] = (circle.getFillColor().b/255.f);
		color[3] = (circle.getFillColor().a/255.f);
	};
	void OnPostUpdate() override { 
		circle.setRadius(radius);
		circle.setFillColor(Conversion::floatToColor(color));
	};

};