#define NOMINMAX
#include <windows.h>
#include <Engine.h>

#include "Intro.h"

Engine* engine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    engine = Engine::GetInstance();
    engine->onStarted = []() {
        engine->sceneHandler.pushScene("intro", std::make_shared<GAME::Intro>());
        engine->sceneHandler.setActive("intro");
    };
    engine->init(true, { 900, 500 }, "Engine");
    return 0;
}