#pragma once

#include "../Generic/Entity.h"

#include <vector>
#include <memory>

class EntityHandler {
public:
	std::vector<std::shared_ptr<Entity>> entities;
	void sort(); //Organize entities by layer.
	
	void preUpdate();
	void updateEntities(const int& dt); //Tick
	
	void pushEntity(const std::shared_ptr<Entity>& entity);
	void remove(std::shared_ptr<Entity> e);
};