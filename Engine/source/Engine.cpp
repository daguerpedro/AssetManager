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

void Engine::init(ImVec2 winsize, const std::string& title)
{
#ifdef _DEBUG
    guiHandler.pushContainer(std::make_shared<EditorContainer>());
    
    /// When using a debug version, it wont draw things on the render window, but to a RenderTexture.
    /// So the RenderTexture can act like a viewport.
    auto g = std::make_shared<GameContainer>(); // Game container is just a ImGui window that draw a RenderTexture.
    guiHandler.pushContainer(g);
#endif
    window.create(sf::VideoMode(winsize.x, winsize.y), title);
    ImGui::SFML::Init(window);

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::Clock c_sfml;
    sf::Clock c_time;

#ifdef _DEBUG
    rtarget = &g->rt; //If using a debug version, the render target will be a ImGui Window.
#endif
#ifdef _NDEBUG
    rtarget = &window; //If not a debug version, just use the RenderWindow.
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

        const float dt = c_time.restart().asSeconds();

        ImGui::SFML::Update(window, c_sfml.restart());
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, 0, ImGuiDockNodeFlags_PassthruCentralNode);
        
        window.clear();

        if (rtarget != nullptr)
        {
            //TODO: Make a color conversion function.
            //Clear the render using a color setted via Config.
            rtarget->clear(Conversion::floatToColor(Config::color_bg));
        }

        //tick

        globalEntityHandler.preUpdate();
        sceneHandler.preUpdateScene();

        guiHandler.updateGuis(dt);
        globalEntityHandler.updateEntities(dt);
        sceneHandler.updateScene(dt);

        globalEntityHandler.postUpdate();
        sceneHandler.postUpdateScene();

#ifdef _DEBUG
        console.draw();
#endif // _DEBUG

        ImGui::SFML::Render(window);
        window.display();

        if (!_started)
        {
            if (onStarted)
                onStarted();
            
            _started = true;
        }
    }

    ImGui::SFML::Shutdown();
}