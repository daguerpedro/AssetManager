#include "GuiHandler.h"

void GuiHandler::pushContainer(const std::shared_ptr<Container>& container)
{
	this->containers.emplace_back(container);
}

void GuiHandler::updateGuis(const float& dt)
{
	for (auto& container : containers)
		container->onUpdate(dt);
}

GuiHandler::GuiHandler()
{
	containers.clear();
}

GuiHandler::~GuiHandler()
{
}