#pragma once

#include "Cell.hpp"

class Grid : public sf::Drawable {
    static inline constexpr int length = 9;

    std::array<std::array<Cell, length>, length> m_grid;
    std::array<std::array<sf::RectangleShape, 3>, 3> m_boxes;
    Cell* m_active_cell { m_grid[0].data() };

public:
    Grid(const sf::Font& font);

    void highlight(const sf::Vector2f& position);
    void input(const sf::Keyboard::Key& key);
    void draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const override;
};
