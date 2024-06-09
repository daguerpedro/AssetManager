#include "SceneHandler.h"
#include "../Engine.h"

void SceneHandler::setActive(const std::string& name)
{
	for (auto& pair : this->scenes)
		if (pair.first == name)
		{
			if (active != nullptr)
				if (active != pair.second)
					active->onDisable();

			Engine::GetInstance()->console.log({ "[SCENE] Switching from " + activeName + " to " + pair.first });

			active = pair.second;
			activeName = pair.first;
			active->onEnable();
			break;
		}
}