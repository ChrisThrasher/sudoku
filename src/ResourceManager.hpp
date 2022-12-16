#pragma once

#include <SFML/Graphics/Font.hpp>

inline const auto& get_font()
{
    static auto font = [] {
        auto font = sf::Font();
        if (!font.loadFromFile(FONT_PATH / std::filesystem::path("font.ttf")))
            throw std::runtime_error("Failed to load font");
        return font;
    }();
    return font;
}
