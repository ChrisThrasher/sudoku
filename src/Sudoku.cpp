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
        for (auto event = sf::Event(); window.pollEvent(event);) {
            auto& state = *states.top();
            if (event.type == sf::Event::Closed)
                window.close();
            if (!state.update(event)) {
                if (auto next_state = state.next_state())
                    states.push(std::move(next_state));
                else if (states.size() > 1)
                    states.pop();
                break;
            }
        }

        window.clear();
        window.draw(*states.top());
        window.display();
    }
}
