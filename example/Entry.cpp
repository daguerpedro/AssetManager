#define NOMINMAX
#include <windows.h>

#include "..\Engine\Engine.h"

void graphics()
{
    Engine* engine = Engine::GetInstance();
    engine->init({ 650, 500 }, "Game example");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    sf::Thread thread(&graphics);
    thread.launch();

    return 0;
}