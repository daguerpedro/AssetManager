#pragma once

#include "..\Generic\Scene.h"

#include <memory>
#include <list>

class SceneHandler
{
public:
	~SceneHandler() = default;
	SceneHandler() = default;

	inline void pushScene(const std::string& name, const std::shared_ptr<Scene>& scene) 
	{
		scenes.emplace_back(name, scene);
	};
	inline void preUpdateScene()
	{
		if (active != nullptr)
			active->preUpdate();
	};

	inline void updateScene(const float& dt)
	{
		if (active != nullptr)
			active->update(dt);
	};

	inline void postUpdateScene()
	{
		if (active != nullptr)
			active->postUpdate();
	};

	void setActive(const std::string& name);

	std::shared_ptr<Scene> active;
	std::string activeName = "";
private:
	std::list<std::pair<std::string, std::shared_ptr<Scene>>> scenes;

};