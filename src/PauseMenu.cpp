#include "PauseMenu.hpp"
#include "Cell.hpp"
#include "ResourceManager.hpp"

#include <SFML/Graphics/Font.hpp>

PauseMenu::PauseMenu()
{
    m_text.setFont(get_font(DATA_DIR / std::filesystem::path("font.ttf")));
    m_text.setString("Game Paused");
    m_text.setCharacterSize(48);

    m_text.setPosition(sf::Vector2f(9u * Cell::size) / 2.f);
    m_text.setOrigin({ m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2,
                       m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2 });
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
