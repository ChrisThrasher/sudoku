#include "PauseMenu.hpp"
#include "ResourceManager.hpp"

#include <SFML/Graphics/Font.hpp>

PauseMenu::PauseMenu()
{
    m_text.setFont(get_font());
    m_text.setString("Game Paused");
    m_text.setCharacterSize(24);

    // FIXME: Center in the window
    m_text.setPosition({ 200, 200 });
}

auto PauseMenu::update(const sf::Event& event) -> std::variant<bool, std::unique_ptr<State>>
{
    switch (event.type) {
    case sf::Event::MouseButtonPressed:
        return false;
    default:
        break;
    }

    return true;
}

void PauseMenu::draw(sf::RenderTarget& target, const sf::RenderStates& /* states */) const { target.draw(m_text); }
