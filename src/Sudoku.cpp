#include "Game.hpp"
#include "State.hpp"

#include <memory>
#include <stack>

int main()
{
    auto font = sf::Font();
    if (!font.loadFromFile(FONT_PATH / std::filesystem::path("font.ttf")))
        throw std::runtime_error("Failed to load font");

    auto window = sf::RenderWindow(sf::VideoMode(9u * Cell::size), "Sudoku");
    window.setFramerateLimit(60);

    auto states = std::stack<std::unique_ptr<State>>();
    states.push(std::make_unique<Game>(font));

    while (window.isOpen()) {
        const auto overload
            = Overload { [&states](bool is_running) {
                            if (!is_running)
                                states.pop();
                        },
                         [&states](std::unique_ptr<State> new_state) { states.push(std::move(new_state)); } };

        for (auto event = sf::Event(); window.pollEvent(event);) {
            auto& state = *states.top();
            if (event.type == sf::Event::Closed)
                window.close();
            std::visit(overload, state.update(event));
        }

        window.clear();
        window.draw(*states.top());
        window.display();
    }
}
