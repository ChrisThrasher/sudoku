#include "PauseMenu.hpp"

PauseMenu::PauseMenu()
{
    // FIXME: Reuse same font from main()
    static auto font = sf::Font();
    if (!font.loadFromFile(FONT_PATH / std::filesystem::path("font.ttf")))
        throw std::runtime_error("Failed to load font");

    m_text.setFont(font);
    m_text.setString("Game Paused");
    m_text.setCharacterSize(24);

    // FIXME: Center in the window
    m_text.setPosition({ 200, 200 });
}

auto PauseMenu::update(const sf::Event& event) -> bool
{
    assert(!m_next_state);

    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        return false;
    default:
        break;
    }

    return true;
}

void PauseMenu::draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const { target.draw(m_text); }
