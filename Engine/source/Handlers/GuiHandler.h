#pragma once
#include "../Generic/Container.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class GuiHandler
{
public:
	GuiHandler();
	~GuiHandler();

	void pushContainer(const std::shared_ptr<Container>& container);
	void updateGuis(const int& dt);
private:
	std::vector<std::shared_ptr<Container>> containers;

};