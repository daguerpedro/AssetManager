#include "Entity.h"
#include "..\Engine.h"

void Entity::setLayer(const unsigned int& layer)
{
	_layer = layer;
	//TODO: SORT SCENE.
	Engine::console.log("[ENTITY.CPP LINE 8] TODO: SORT SCENE ENTITES.");
	Engine::GetInstance()->globalEntityHandler.sort();
}

unsigned int& Entity::getLayer()
{
	return _layer; 
}

void Entity::postUpdate()
{
	this->transformable->setPosition(this->position[0], this->position[1]);
	this->transformable->setRotation(this->rotation);
	this->transformable->setScale(this->scale[0], this->scale[1]);

	if (Layer < 0) Layer = 0;
	if (Layer != getLayer() && Layer >= 0) setLayer(Layer);
	this->OnPostUpdate();
}

void Entity::preUpdate()
{
	this->position[0] = this->transformable->getPosition().x;
	this->position[1] = this->transformable->getPosition().y;

	this->rotation = this->transformable->getRotation();

	this->scale[0] = this->transformable->getScale().x;
	this->scale[1] = this->transformable->getScale().y;
	this->onPreUpdate();
}