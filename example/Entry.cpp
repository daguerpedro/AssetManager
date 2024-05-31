#define NOMINMAX
#include <windows.h>

#include "..\Engine\source\Engine.h"
#include <Entities/Text.h>
#include <thread>

class Test : public Scene
{
    std::shared_ptr<Text> eta;
    sf::Font font;
public:
    Test()
    {
        if (!font.loadFromFile("./arial.ttf"))
        {
            Engine::console.log("Failed to load arial.ttf");
        }

        eta = std::make_shared<Text>(0, "Title", font, 35);
        eta->primitive.setFillColor(sf::Color::Black);

        this->sceneEntityHandler.pushEntity(eta);
    };

    void onEnable() override
    {
        Engine::console.log("Test enabled");       
    };

    void onDisable() override
    {
        Engine::console.log("Test disabled");
    };

    void onUpdate(const float& dt) override
    {

    };

    void onPreUpdate() override
    {
    };

    void onPostUpdate() override
    {

    };
};

Engine* engine;

void OThread()
{
    engine->sceneHandler.pushScene("test", std::make_shared<Test>());
    engine->sceneHandler.setActive("test");
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    engine = Engine::GetInstance();
    engine->onStarted = []() {
        std::thread scenest = std::thread(OThread);
        scenest.detach();
    };
    engine->init(true, { 650, 500 }, "Engine");
    return 0;
}