#include "EntityHandler.h"
#include <algorithm>
#include <Engine.h>

void EntityHandler::preUpdate()
{
	for (auto& entity : entities)
		if (entity->enabled)
			entity->preUpdate();
}
void EntityHandler::updateEntities(const int& dt)
{
	for (auto& entity : entities)
		if (entity->enabled)
		{
			entity->OnUpdate(dt);
			entity->postUpdate();

			Engine::GetInstance()->rtarget->draw(*entity->drawAble);
		}
}

void EntityHandler::pushEntity(const std::shared_ptr<Entity>& entity)
{
	entities.emplace_back(entity);
	sort();
}

void EntityHandler::sort()
{
	std::sort(entities.begin(), entities.end(), [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
		return a->getLayer() < b->getLayer();
	});
}

void EntityHandler::remove(std::shared_ptr<Entity> e)
{	
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[&e](const std::shared_ptr<Entity>& ptr) {
			return ptr == e;
		}),
		entities.end());

	e->~Entity();
	sort();
}