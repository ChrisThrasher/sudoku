#include "Grid.hpp"

int main()
{
    auto font = sf::Font();
    if (!font.loadFromFile(FONT_PATH / std::filesystem::path("font.ttf")))
        throw std::runtime_error("Failed to load font");
    auto grid = Grid(font);

    auto window = sf::RenderWindow(sf::VideoMode(9u * Cell::size), "Sudoku");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                grid.highlight({ float(event.mouseButton.x), float(event.mouseButton.y) });
                break;
            case sf::Event::KeyPressed:
                grid.input(event.key.code);
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(grid);
        window.display();
    }
}
