#pragma once
#include "../Generic/Container.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class GuiHandler
{
public:
	GuiHandler() = default;
	~GuiHandler() = default;

	void pushContainer(const std::shared_ptr<Container>& container)
	{
		this->containers.emplace_back(container);
	};

	void updateGuis(const float& dt)
	{
		for (auto& container : containers)
			container->onUpdate(dt);
	};
private:
	std::vector<std::shared_ptr<Container>> containers;

};