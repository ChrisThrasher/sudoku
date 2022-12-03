#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

class State : public sf::Drawable {
protected:
    std::unique_ptr<State> m_next_state;

public:
    virtual ~State() = default;

    [[nodiscard]] virtual bool update(const sf::Event& event) = 0;
    [[nodiscard]] auto next_state() { return std::move(m_next_state); }
};
