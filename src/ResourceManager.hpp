#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

inline const auto& get_font()
{
    static auto font = [] {
        auto font = sf::Font();
        if (!font.loadFromFile(DATA_DIR / std::filesystem::path("font.ttf")))
            throw std::runtime_error("Failed to load font");
        return font;
    }();
    return font;
}

inline const auto& get_click_sound()
{
    static auto buffer = [] {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("click.wav")))
            throw std::runtime_error("Failed to load click sound");
        return buffer;
    }();
    return buffer;
}

inline const auto& get_good_sound()
{
    static auto buffer = [] {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("good.wav")))
            throw std::runtime_error("Failed to load click sound");
        return buffer;
    }();
    return buffer;
}

inline const auto& get_bad_sound()
{
    static auto buffer = [] {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("bad.wav")))
            throw std::runtime_error("Failed to load click sound");
        return buffer;
    }();
    return buffer;
}
