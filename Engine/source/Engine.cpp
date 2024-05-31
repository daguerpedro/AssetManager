#include "Engine.h"
#include "GUI/EditorContainer.h"
#include "GUI/GameContainer.h"

Engine* Engine::_engine = nullptr;

Engine::Engine()
{
    io = nullptr;
}

Engine::~Engine()
{
}

Console Engine::console{};

Engine* Engine::GetInstance()
{
    if (_engine == nullptr) {
        _engine = new Engine();
    }
    return _engine;
}

void Engine::configStyle()
{
    auto style = &ImGui::GetStyle();
    style->WindowPadding = { 5, 5 };
    style->FramePadding = { 6, 5 };
    style->SeparatorTextPadding = { 20, 3 };

    style->DockingSeparatorSize = 1;

    style->ItemSpacing = { 7, 5 };
    style->ItemInnerSpacing = { 4, 4 };

    style->ChildBorderSize = 0;
    style->FrameBorderSize = 0;
    style->PopupBorderSize = 0;
    style->WindowBorderSize = 0;
    style->TabBarBorderSize = 0;
    style->TabBorderSize = 0;
    style->SeparatorTextBorderSize = 1;

    style->WindowRounding = 2;
    style->ChildRounding = 0;
    style->FrameRounding = 3;
    style->TabRounding = 0;
    
    style->WindowTitleAlign = { .5, .5 };
    style->SeparatorTextAlign = { .5, .5 };

    style->WindowMenuButtonPosition = ImGuiDir_None;
    style->ColorButtonPosition = ImGuiDir_Left;


}

void Engine::init(bool enableEditor, ImVec2 winsize, const std::string& title)
{
    window.create(sf::VideoMode(winsize.x, winsize.y), title);
    ImGui::SFML::Init(window);

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    configStyle();

    sf::Clock c_sfml;
    sf::Clock c_time;

    renderTarget = &window;

    if (enableEditor)
    {
        guiHandler.pushContainer(std::make_shared<EditorContainer>());
        auto gameContainer = std::make_shared<GameContainer>(); // Game container is just a ImGui window that draw a RenderTexture.
        guiHandler.pushContainer(gameContainer);
        renderTarget = &gameContainer->rt;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const float dt = c_time.restart().asSeconds();

        ImGui::SFML::Update(window, c_sfml.restart());
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, 0, ImGuiDockNodeFlags_PassthruCentralNode);

        window.clear();

        if (renderTarget != nullptr)
            renderTarget->clear(Conversion::floatToColor(Config::color_bg));

        //tick

        globalEntityHandler.preUpdate();
        sceneHandler.preUpdateScene();

        guiHandler.updateGuis(dt); //Gui doesnt need preUpdates nor postUpdates.
        globalEntityHandler.updateEntities(dt);
        sceneHandler.updateScene(dt);

        globalEntityHandler.postUpdate();
        sceneHandler.postUpdateScene();

        if (enableEditor)
            console.draw();

        ImGui::SFML::Render(window);
        window.display();

        if (!started)
        {
            if (onStarted)
                onStarted();

            started = true;
        }
    }

    ImGui::SFML::Shutdown();
}