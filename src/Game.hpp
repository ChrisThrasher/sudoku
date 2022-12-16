#pragma once

#include "Cell.hpp"
#include "State.hpp"

#include <array>

class Game : public State {
    static inline constexpr int length = 9;

    std::array<std::array<Cell, length>, length> m_grid;
    std::array<std::array<sf::RectangleShape, 3>, 3> m_boxes;
    Cell* m_active_cell { m_grid[0].data() };
    sf::RenderWindow& m_window;

    void highlight(const sf::Vector2f& position);
    void input(const sf::Keyboard::Key& key);

public:
    Game(sf::RenderWindow& window);
    auto update(const sf::Event& event) -> std::variant<bool, std::unique_ptr<State>> override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const override;
};
