#define NOMINMAX
#include <windows.h>

#include "..\Engine\source\Engine.h"
#include <Entities/Circle.h>
#include <thread>

class Test : public Scene
{
    std::shared_ptr<Circle> c;
    float acc = 0;
    float speed = 25;
public:
    Test()
    {
        c = std::make_shared<Circle>(0, new float[] {0, 0, 1, 1}, 65, 30);
        this->sceneEntityHandler.pushEntity(c);
    };

    void onEnable() override
    {
        Engine::console.log("Test enabled");
        c->position[0] = Engine::GetInstance()->rtarget->getView().getSize().x / 2;
        c->position[1] = Engine::GetInstance()->rtarget->getView().getSize().y / 2;

    };
    void onDisable() override
    {
        Engine::console.log("Test disabled");
    };
    void onUpdate(const float& dt) override
    {
        acc += 1 * dt;
        c->position[0] += speed * dt;
        if (acc >= 5)
        {
            acc = 0;
            c->position[0] = Engine::GetInstance()->rtarget->getView().getSize().x / 2;
            c->position[1] = Engine::GetInstance()->rtarget->getView().getSize().y / 2;
        }
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
    engine->init({ 650, 500 }, "Engine");
    return 0;
}