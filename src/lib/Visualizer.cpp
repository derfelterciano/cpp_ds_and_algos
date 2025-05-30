#include "Visualizer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <thread>

#include "Utilities.hpp"

// helpers
namespace {

// Draws the maze given a window
void draw_maze(sf::RenderWindow& window, const Maze& maze,
               const ds::Vector<vrtx>& path = {}) {
    // rendering params
    const int cell_size = 24;
    int       rows = maze.rows(), cols = maze.cols();

    window.clear(sf::Color::White);

    // draw grid cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++i) {
            int x = j * cell_size;
            int y = i * cell_size;

            const Cell& c = maze.cell(i, j);

            sf::RectangleShape rect(sf::Vector2f(cell_size, cell_size));
            rect.setPosition({float(x), float(y)});
            rect.setFillColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            // draw walls

            sf::VertexArray walls(sf::PrimitiveType::Lines);
            if (c.top_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(x, y);
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position = sf::Vector2f(x + cell_size, y);
                vertex2.color    = sf::Color::Black;
                walls.append(vertex2);
            }

            if (c.bottom_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(x, y + cell_size);
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position = sf::Vector2f(x + cell_size, y + cell_size);
                vertex2.color    = sf::Color::Black;
                walls.append(vertex2);
            }
        }
    }
}

};  // namespace
