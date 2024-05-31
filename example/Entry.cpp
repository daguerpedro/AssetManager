#define NOMINMAX
#include <windows.h>

#include "..\Engine\source\Engine.h"
#include <Entities/Text.h>
#include <thread>
#include <format>

class Test : public Scene
{
    std::shared_ptr<Text> text_eta;
    std::shared_ptr<Text> text_scenename;

    float elapsed = 0;
public:
    Test()
    {
        auto font = std::make_shared<sf::Font>();
        if (!font->loadFromFile("./arial.ttf"))
        {
            Engine::console.log("Failed to load arial.ttf");
        }

        Engine::GetInstance()->fontHandler.addFont("arial", font);

        text_eta = std::make_shared<Text>(0, "ETA: 0s", *font, 15);
        text_eta->primitive.setFillColor(sf::Color::White);
     
        text_scenename = std::make_shared<Text>(0, "SCENE", *font, 15);
        text_scenename->primitive.setFillColor(sf::Color::White);
        text_scenename->primitive.setPosition(25, 25);

        this->sceneEntityHandler.pushEntity(text_eta);
        Engine::GetInstance()->globalEntityHandler.pushEntity(text_scenename);
    };

    void onEnable() override
    {
        Engine::console.log("Test enabled");       
        elapsed = 0;
    };

    void onDisable() override
    {
        Engine::console.log("Test disabled");
        elapsed = 0;
    };

    void onUpdate(const float& dt) override
    {
        this->elapsed += 1 * dt;
        std::string s = std::format("ETA: {:.0f}s", elapsed);
        text_eta->primitive.setString(s);

        text_scenename->primitive.setString(std::format("I'M A GLOBAL OBJECT, CREATED ON {} SCENE", Engine::GetInstance()->sceneHandler.activeName));

        if (elapsed >= 10)
            Engine::GetInstance()->sceneHandler.setActive("test2");
    };

    void onPreUpdate() override
    {
    };

    void onPostUpdate() override
    {

    };
};
class Test2 : public Scene
{
    float elapsed = 0;
public:
    void onEnable() override
    {
        Engine::console.log("Test2 enabled");
        elapsed = 0;
    };

    void onDisable() override
    {
        Engine::console.log("Test2 disabled");
        elapsed = 0;
    };

    void onUpdate(const float& dt) override
    {
        this->elapsed += 1 * dt;
        if (elapsed >= 10)
            Engine::GetInstance()->sceneHandler.setActive("test");
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
    engine->sceneHandler.pushScene("test2", std::make_shared<Test2>());

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