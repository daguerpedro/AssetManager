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

void Engine::configureStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(10, 5);
    style->FramePadding = ImVec2(10, 5);
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;

    style->WindowBorderSize = 0;

    style->ScrollbarSize = 10.0f;
    style->GrabMinSize = 5.0f;
    style->DockingSeparatorSize = 0;

    style->FrameRounding = 5.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabRounding = 3.0f;
    style->WindowRounding = 5;

    style->WindowTitleAlign = { .5, .5 };
    style->WindowMenuButtonPosition = ImGuiDir_None;


    style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06f, 0.05f, 0.07f, 0.97f);
    style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.09f, 0.08f, 0.10f, 1.00f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(0.17f, 0.17f, 0.17f, 0.80f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.09f, 0.08f, 0.10f, 1.00f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.06f, 0.05f, 0.07f, 0.86f);
    style->Colors[ImGuiCol_Text] = ImVec4(0.91f, 0.91f, 0.91f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}

void Engine::init(bool enableEditor, ImVec2 winsize, const std::string& title)
{
    window.create(sf::VideoMode(winsize.x, winsize.y), title);
    ImGui::SFML::Init(window);

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    configureStyle();

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

		sf::Color c= sf::Color::Black;
        if (renderTarget != nullptr)
        {
            if (Engine::GetInstance()->sceneHandler.active != nullptr)
                c = Conversion::floatToColor(Engine::GetInstance()->sceneHandler.active->backColor);

            renderTarget->clear(c);
        }

        //tick

        sceneHandler.preUpdateScene();

        guiHandler.updateGuis(dt); //Gui doesnt need preUpdates nor postUpdates.
        sceneHandler.updateScene(dt);

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