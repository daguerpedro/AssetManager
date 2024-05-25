#pragma once

#include <SFML/Graphics.hpp>

class Entity {
protected:
	unsigned int _layer;

public:
	inline Entity(const unsigned int& layer) {
		_layer = layer;
		enabled = true;
	}
	
	sf::Drawable* drawAble = nullptr;
	sf::Transformable* transformable = nullptr;

	virtual ~Entity() = default;
	virtual void OnUpdate(const int& dt) = 0;
	
	void setLayer(const unsigned int& layer);

	unsigned int& getLayer();

	bool enabled;
};