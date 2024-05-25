#pragma once
#include "Container.h"
#include <memory>
#include <vector>

class GuiHandler
{
public:
	GuiHandler();
	~GuiHandler();

	void pushContainer(const std::shared_ptr<Container>& container);
	void updateGuis();
private:
	std::vector<std::shared_ptr<Container>> containers;

};