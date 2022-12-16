#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <variant>

class State : public sf::Drawable {
public:
    State() = default;
    ~State() override = default;
    State(const State&) = default;
    State& operator=(const State&) = default;
    State(State&&) noexcept = default;
    State& operator=(State&&) noexcept = default;

    [[nodiscard]] virtual auto update(const sf::Event& event) -> std::variant<bool, std::unique_ptr<State>> = 0;
};
