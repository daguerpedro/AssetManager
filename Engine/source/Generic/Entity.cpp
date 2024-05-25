#include "Entity.h"
#include "..\Engine.h"

void Entity::setLayer(const unsigned int& layer)
{
	_layer = layer;
	Engine::GetInstance()->entityHandler.sort();
}

unsigned int& Entity::getLayer()
{
	return _layer; 
}
