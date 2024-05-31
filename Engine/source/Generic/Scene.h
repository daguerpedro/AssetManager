#pragma once
#include "../Handlers/EntityHandler.h"
class Scene
{
public:
    EntityHandler sceneEntityHandler;
    virtual void onEnable() = 0;
    virtual void onDisable() = 0;

    virtual void onUpdate(const float& dt) = 0;
    virtual void onPreUpdate() = 0;
    virtual void onPostUpdate() = 0;

    inline void update(const float& dt)
    { 
        onUpdate(dt); 
        sceneEntityHandler.updateEntities(dt);
    };
    inline void preUpdate() 
    { 
        onPreUpdate(); 
        sceneEntityHandler.preUpdate();
    };
    inline void postUpdate()
    { 
        onPostUpdate(); 
        sceneEntityHandler.postUpdate();
    };

};