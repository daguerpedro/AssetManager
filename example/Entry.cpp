#define NOMINMAX
#include <windows.h>

#include ".\Engine\Engine.h"
#include ".\GUI\EditorContainer.h"
#include ".\GUI\GameContainer.h"

void graphics()
{
    Engine engine = Engine();

#ifdef _DEBUG
    engine.guiHandler.pushContainer(std::make_shared<EditorContainer>());
#endif
    engine.guiHandler.pushContainer(std::make_shared<GameContainer>());

    engine.init({ 650, 500 }, "Game example");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    sf::Thread thread(&graphics);
    thread.launch();

    return 0;
}