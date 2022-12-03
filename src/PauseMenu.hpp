#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"

class PauseMenu : public State {
    sf::Text m_text;

public:
    PauseMenu();
    auto update(const sf::Event& event) -> bool override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const override;
};
