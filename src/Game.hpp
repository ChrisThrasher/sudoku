#pragma once

#include "Cell.hpp"
#include "State.hpp"

class Game : public State {
    static inline constexpr int length = 9;

    std::array<std::array<Cell, length>, length> m_grid;
    std::array<std::array<sf::RectangleShape, 3>, 3> m_boxes;
    Cell* m_active_cell { m_grid[0].data() };

    void highlight(const sf::Vector2f& position);
    void input(const sf::Keyboard::Key& key);

public:
    Game(const sf::Font& font);
    auto update(const sf::Event& event) -> bool override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const override;
};