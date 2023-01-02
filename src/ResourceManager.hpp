#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

#include <filesystem>

const sf::SoundBuffer& get_sound_buffer(std::filesystem::path path);
const sf::Font& get_font(std::filesystem::path path);
