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
	virtual void onPreUpdate() = 0;
	virtual void OnPostUpdate() = 0;


	void preUpdate(); //Pre-update will get values from transformable and dump in Entity variables.
	//Between preUpdate and Update, the GUI should bge rendered.
	void postUpdate(); //Post-update will get values from Entity and dump in Transformable variables.
	void setLayer(const unsigned int& layer);

	unsigned int& getLayer();
	int Layer = 1;

	float position[2] = { 0, 0 };
	float scale[2] = { 1, 1 };

	float rotation = 0;

	bool enabled;
};