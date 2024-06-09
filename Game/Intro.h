#pragma once

#include <Engine.h>
#include <Entities/Text.h>

namespace GAME 
{
	class Intro : public Scene
	{
        std::shared_ptr<Text> titulo;
        std::shared_ptr<sf::Font> font;

        bool initialSetup = true;

        void onEnable() override 
        {
            if (initialSetup)
            {
                auto raw = std::make_shared<sf::Font>();
                raw->loadFromFile("arial.ttf");

                Engine::GetInstance()->fontHandler.addFont("arial", raw);
                font = Engine::GetInstance()->fontHandler.getFont("arial");

                titulo = std::make_shared<Text>(10, "titulo", "EXAMPLE", *font, 40);
                this->sceneEntityHandler.pushEntity(titulo);

                initialSetup = false;

                auto view = Engine::GetInstance()->renderTarget->getView();
                titulo->transformable->setPosition(view.getCenter());
            }

            titulo->primitive.setFillColor(sf::Color::White);
            Engine::GetInstance()->console.log("Intro enabled");

            titulo->enabled = true;
        };
        
        void onDisable() override 
        {
            titulo->enabled = false;
        };

        void onUpdate(const float& dt) override 
        {

        };

        void onPreUpdate() override { };
        void onPostUpdate() override { };
	};
}