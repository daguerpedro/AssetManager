#define NOMINMAX
#include <windows.h>

#include "..\Engine\source\Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    Engine* engine = Engine::GetInstance();
    engine->init({ 650, 500 }, "Engine");

    return 0;
}