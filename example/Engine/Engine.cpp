#include "Engine.h"

Engine::Engine()
{
    guiHandler = GuiHandler();
}

Engine::~Engine()
{
}

void Engine::init(ImVec2 winsize, const std::string& title)
{
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