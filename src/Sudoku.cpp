#include "Game.hpp"

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
            // Handle window close at a global level
            if (event.type == sf::Event::Closed)
                window.close();

            // Update the current state
            auto status = states.top()->update(event);

            // Handle potential return types
            if (std::holds_alternative<bool>(status))
                if (!std::get<bool>(status))
                    states.pop();
            if (std::holds_alternative<std::unique_ptr<State>>(status))
                states.push(std::move(std::get<std::unique_ptr<State>>(status)));
        }

        window.clear();
        window.draw(*states.top());
        window.display();
    }
}
