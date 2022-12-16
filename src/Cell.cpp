#include "Cell.hpp"
#include "ResourceManager.hpp"

#include <cassert>

namespace {
constexpr auto highlight_color = sf::Color(64, 64, 64);
constexpr auto default_color = sf::Color(32, 32, 32);
}

Cell::Cell(const sf::Vector2f& position)
    : m_text("", get_font(), Cell::size.y / 2u)
{
    m_shape.setPosition(position);
    m_shape.setFillColor(default_color);
    m_shape.setOutlineThickness(5.f);
    m_shape.setOutlineColor({ 192, 192, 192 });
}

void Cell::test_intersect(const sf::Vector2f& position, Cell*& active_cell)
{
    if (m_shape.getGlobalBounds().contains(position))
        active_cell = this;
}

void Cell::highlight() { m_shape.setFillColor(highlight_color); }

void Cell::unhighlight() { m_shape.setFillColor(default_color); }

void Cell::set_value(const std::optional<int>& value)
{
    m_value = value;
    if (!value.has_value())
        return m_text.setString("");

    assert(*value >= 1);
    assert(*value <= 9);
    m_text.setString(std::to_string(*value));
    m_text.setOrigin({ m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2,
                       m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2 });
    m_text.setPosition(m_shape.getPosition() + sf::Vector2f(Cell::size / 2u));
}

auto Cell::get_value() const -> std::optional<int> { return m_value; }

void Cell::flag() { m_text.setFillColor(sf::Color::Red); }

void Cell::unflag() { m_text.setFillColor(sf::Color::White); }

void Cell::draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const
{
    target.draw(m_shape);
    target.draw(m_text);
}
