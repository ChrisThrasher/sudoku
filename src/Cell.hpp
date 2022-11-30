#pragma once

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape m_shape { sf::Vector2f(size) };
    sf::Text m_text;
    std::optional<int> m_value;

public:
    static inline constexpr sf::Vector2u size { 70, 70 };

    Cell() = default;
    Cell(const sf::Font& font, const sf::Vector2f& position);

    void test_intersect(const sf::Vector2f& position, Cell*& active_cell);
    void highlight();
    void unhighlight();
    void set_value(const std::optional<int>& value);
    auto get_value() const -> std::optional<int>;
    void flag();
    void unflag();
    void draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const override;
};
