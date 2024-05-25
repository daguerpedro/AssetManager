#include "GuiHandler.h"

void GuiHandler::pushContainer(const std::shared_ptr<Container>& container)
{
	this->containers.emplace_back(container);
}

void GuiHandler::updateGuis()
{
	for (auto& container : containers)
		container->onUpdate();
}

GuiHandler::GuiHandler()
{
	containers.clear();
}

GuiHandler::~GuiHandler()
{
}