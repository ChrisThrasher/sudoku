#include "Game.hpp"
#include "PauseMenu.hpp"
#include "ResourceManager.hpp"

#include <SFML/Audio/Sound.hpp>

#include <iostream>

Game::Game(sf::RenderWindow& window)
    : m_window(window)
{
    for (size_t i = 0; i < length; ++i)
        for (size_t j = 0; j < length; ++j)
            m_grid[i][j] = { { float(i) * Cell::size.x, float(j) * Cell::size.y } };

    for (size_t i = 0; i < m_boxes.size(); ++i) {
        for (size_t j = 0; j < m_boxes.size(); ++j) {
            auto& box = m_boxes[i][j];
            box = sf::RectangleShape(sf::Vector2f(3u * Cell::size));
            box.setPosition({ float(i) * 3 * Cell::size.x, float(j) * 3 * Cell::size.y });
            box.setFillColor({ 0, 0, 0, 0 });
            box.setOutlineThickness(5.f);
            box.setOutlineColor({ 192, 192, 192 });
        }
    }
}

auto Game::update(const sf::Event& event) -> std::variant<bool, std::unique_ptr<State>>
{
    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        highlight(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
            return std::make_unique<PauseMenu>();
        input(event.key.code);
        break;
    default:
        break;
    }

    return true;
}

void Game::highlight(const sf::Vector2f& position)
{
    static auto click_sound = sf::Sound(get_sound_buffer(DATA_DIR / std::filesystem::path("click.wav")));

    m_active_cell->unhighlight();
    for (auto& row : m_grid)
        for (auto& cell : row)
            cell.test_intersect(position, m_active_cell);
    m_active_cell->highlight();
    click_sound.play();
}

void Game::input(const sf::Keyboard::Key& key)
{
    switch (key) {
    case sf::Keyboard::Num0:
    case sf::Keyboard::Backspace:
        m_active_cell->set_value(std::nullopt);
        break;
    case sf::Keyboard::Num1:
        m_active_cell->set_value(1);
        break;
    case sf::Keyboard::Num2:
        m_active_cell->set_value(2);
        break;
    case sf::Keyboard::Num3:
        m_active_cell->set_value(3);
        break;
    case sf::Keyboard::Num4:
        m_active_cell->set_value(4);
        break;
    case sf::Keyboard::Num5:
        m_active_cell->set_value(5);
        break;
    case sf::Keyboard::Num6:
        m_active_cell->set_value(6);
        break;
    case sf::Keyboard::Num7:
        m_active_cell->set_value(7);
        break;
    case sf::Keyboard::Num8:
        m_active_cell->set_value(8);
        break;
    case sf::Keyboard::Num9:
        m_active_cell->set_value(9);
        break;
    default:
        return;
    }

    if (!m_active_cell->get_value().has_value())
        return;

    // Determine what cell was clicked on
    auto active_cell_coordinates = sf::Vector2<size_t>();
    for (size_t i = 0; i < length; ++i)
        for (size_t j = 0; j < length; ++j)
            if (&m_grid[i][j] == m_active_cell)
                active_cell_coordinates = { i, j };

    // Consolidate invalid input logic
    const auto handle_invalid_input = [this] {
        static auto bad_sound = sf::Sound(get_sound_buffer(DATA_DIR / std::filesystem::path("bad.wav")));
        bad_sound.play();
        m_active_cell->flag();
    };

    // Check for same number in row
    for (size_t i = 0; i < length; ++i) {
        const auto& cell = m_grid[i][active_cell_coordinates.y];
        if (&cell == m_active_cell)
            continue;
        if (cell.get_value() == m_active_cell->get_value())
            return handle_invalid_input();
    }

    // Check for same number in column
    for (size_t j = 0; j < length; ++j) {
        const auto& cell = m_grid[active_cell_coordinates.x][j];
        if (&cell == m_active_cell)
            continue;
        if (cell.get_value() == m_active_cell->get_value())
            return handle_invalid_input();
    }

    // Check for same number in box
    const auto active_box_coordinates = sf::Vector2<size_t>(active_cell_coordinates.x - active_cell_coordinates.x % 3,
                                                            active_cell_coordinates.y - active_cell_coordinates.y % 3);
    for (size_t i = active_box_coordinates.x; i < active_box_coordinates.x + 3; ++i) {
        for (size_t j = active_box_coordinates.y; j < active_box_coordinates.y + 3; ++j) {
            const auto& cell = m_grid[i][j];
            if (&cell == m_active_cell)
                continue;
            if (cell.get_value() == m_active_cell->get_value())
                return handle_invalid_input();
        }
    }

    static auto good_sound = sf::Sound(get_sound_buffer(DATA_DIR / std::filesystem::path("good.wav")));
    good_sound.play();
    m_active_cell->unflag();
}

void Game::draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const
{
    for (const auto& row : m_grid)
        for (const auto& cell : row)
            target.draw(cell);
    for (const auto& row : m_boxes)
        for (const auto& box : row)
            target.draw(box);
}
