#pragma once

#include "../Generic/Entity.h"

#include <vector>
#include <memory>

class EntityHandler {
public:
	std::vector<std::shared_ptr<Entity>> entities;
	void sort();
	void remove(std::shared_ptr<Entity> e);
	void updateEntities(const int& dt);
	void pushEntity(const std::shared_ptr<Entity>& entity);
};