#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <variant>

class State : public sf::Drawable {
public:
    virtual ~State() = default;

    [[nodiscard]] virtual auto update(const sf::Event& event) -> std::variant<bool, std::unique_ptr<State>> = 0;
};

template <class... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;
