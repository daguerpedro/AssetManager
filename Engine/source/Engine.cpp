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

Engine::Console Engine::console;

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
    
    auto g = std::make_shared<GameContainer>();
    guiHandler.pushContainer(g);
#endif
    //TODO: IF ITS NOT DEBUG, JUST RENDER INSIDE THE SFML WINDOW!

    window.create(sf::VideoMode(winsize.x, winsize.y), title);
    ImGui::SFML::Init(window);

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::Clock c_sfml;
    sf::Clock c_time;

#ifdef _DEBUG
    rtarget = &g->rt;
#endif
#ifdef _NDEBUG
    rtarget = &window;
#endif

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const int dt = c_time.restart().asMilliseconds();

        ImGui::SFML::Update(window, c_sfml.restart());
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, 0, ImGuiDockNodeFlags_PassthruCentralNode);
        
        window.clear();

        if (rtarget != nullptr)
        {
            rtarget->clear({
                static_cast<uint8_t>(Config::color_bg[0] * 255),
                static_cast<uint8_t>(Config::color_bg[1] * 255),
                static_cast<uint8_t>(Config::color_bg[2] * 255),
                static_cast<uint8_t>(Config::color_bg[3] * 255)
             });
        }

        guiHandler.updateGuis(dt);
        entityHandler.updateEntities(dt);

#ifdef _DEBUG
        console.draw();
#endif // _DEBUG

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}