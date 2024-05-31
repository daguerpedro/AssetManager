#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class FontHandler
{
public:
    FontHandler() = default;
    ~FontHandler() = default;

    std::shared_ptr<sf::Font> getFont(const std::string& name)
    {
        for (auto& values : fonts)
            if (values.first == name)
                return values.second;

        return nullptr;
    }

    void addFont(const std::string& name, const std::shared_ptr<sf::Font>& font)
    {
        fonts.push_back(std::make_pair(name, font));
    }

private:
    std::list<std::pair<std::string, std::shared_ptr<sf::Font>>> fonts;
};
