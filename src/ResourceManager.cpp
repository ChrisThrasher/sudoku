#include "ResourceManager.hpp"

#include <unordered_map>

const sf::SoundBuffer& get_sound_buffer(std::filesystem::path path)
{
    static std::unordered_map<std::filesystem::path::string_type, sf::SoundBuffer> sound_buffers;

    path = std::filesystem::canonical(path);
    const auto maybe_sound_buffer = sound_buffers.find(path);
    if (maybe_sound_buffer != sound_buffers.end())
        return maybe_sound_buffer->second;
    auto buffer = sf::SoundBuffer();
    if (!buffer.loadFromFile(path))
        throw std::runtime_error("Failed to load sound from path " + path.string());
    return sound_buffers[path.string()] = buffer;
}

const sf::Font& get_font(std::filesystem::path path)
{
    static std::unordered_map<std::filesystem::path::string_type, sf::Font> fonts;

    path = std::filesystem::canonical(path);
    const auto maybe_font = fonts.find(path);
    if (maybe_font != fonts.end())
        return maybe_font->second;
    auto font = sf::Font();
    if (!font.loadFromFile(path))
        throw std::runtime_error("Failed to load font from path " + path.string());
    return fonts[path.string()] = font;
}

#if 0

inline const auto& get_click_sound()
{
    static const auto sound = [] {
        auto buffer = sf::SoundBuffer();
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("click.wav")))
            throw std::runtime_error("Failed to load click sound");
        auto sound = sf::Sound(buffer);
        // sound.setVolume(50);
        return sound;
    }();
    return sound;
}

inline const auto& get_good_sound()
{
    static const auto sound = [] {
        auto buffer = sf::SoundBuffer();
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("good.wav")))
            throw std::runtime_error("Failed to load click sound");
        auto sound = sf::Sound(buffer);
        // sound.setVolume(50);
        return sound;
    }();
    return sound;
}

inline const auto& get_bad_sound()
{
    static const auto sound = [] {
        auto buffer = sf::SoundBuffer();
        if (!buffer.loadFromFile(DATA_DIR / std::filesystem::path("bad.wav")))
            throw std::runtime_error("Failed to load click sound");
        auto sound = sf::Sound(buffer);
        // sound.setVolume(50);
        return sound;
    }();
    return sound;
}

inline const auto& get_font()
{
    static const auto font = [] {
        auto font = sf::Font();
        if (!font.loadFromFile(DATA_DIR / std::filesystem::path("font.ttf")))
            throw std::runtime_error("Failed to load font");
        return font;
    }();
    return font;
}

#endif
