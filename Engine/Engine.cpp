#include "Engine.h"
#include "GUI/EditorContainer.h"
#include "GUI/GameContainer.h"

Engine* Engine::_engine = nullptr;

Engine::Engine()
{
    guiHandler = GuiHandler();
}

Engine::~Engine()
{
}

Engine* Engine::GetInstance()
{
    if (_engine == nullptr) {
        _engine = new Engine();
    }
    return _engine;
}

void Engine::init(ImVec2 winsize, const std::string& title)
{
#ifdef _DEBUG
    guiHandler.pushContainer(std::make_shared<EditorContainer>());
    guiHandler.pushContainer(std::make_shared<GameContainer>());
#endif
    //TODO: IF ITS NOT DEBUG, JUST RENDER INSIDE THE SFML WINDOW!

    window.create(sf::VideoMode(winsize.x, winsize.y), title);
    ImGui::SFML::Init(window);

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::Clock dt;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, dt.restart());
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
        
        window.clear();

        guiHandler.updateGuis();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}