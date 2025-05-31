#include "Visualizer.hpp"

#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>

#include "Maze.hpp"
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
    sf::VertexArray walls(sf::PrimitiveType::Lines);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cell_size;
            int y = i * cell_size;

            const Cell& c = maze.cell(i, j);

            sf::RectangleShape rect(sf::Vector2f(cell_size, cell_size));
            rect.setPosition({float(x), float(y)});
            rect.setFillColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color::White);
            window.draw(rect);

            // draw walls
            if (c.top_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(float(x), float(y));
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position = sf::Vector2f(float(x + cell_size), float(y));
                vertex2.color    = sf::Color::Black;
                walls.append(vertex2);
            }

            if (c.bottom_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(float(x), float(y + cell_size));
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position =
                    sf::Vector2f(float(x + cell_size), float(y + cell_size));
                vertex2.color = sf::Color::Black;
                walls.append(vertex2);
            }

            if (c.right_wall) {
                sf::Vertex v1{{float(x + cell_size), float(y)},
                              sf::Color::Black};
                sf::Vertex v2{{float(x + cell_size), float(y + cell_size)},
                              sf::Color::Black};
                walls.append(v1);
                walls.append(v2);
            }

            if (c.left_wall) {
                sf::Vertex v1{{float(x), float(y)}, sf::Color::Black};
                sf::Vertex v2{{float(x), float(y + cell_size)},
                              sf::Color::Black};

                walls.append(v1);
                walls.append(v2);
            }
        }
    }
    window.draw(walls);

    if (!path.is_empty()) {
        sf::VertexArray solution(sf::PrimitiveType::LineStrip, path.len());
        for (std::size_t i = 0; i < path.len(); ++i) {
            int        cx = path[i].second * cell_size + cell_size / 2;
            int        cy = path[i].first * cell_size + cell_size / 2;
            sf::Vertex v{{float(cx), float(cy)}, sf::Color::Red};
            solution[i] = v;
        }
        window.draw(solution);
    }
}
};  // namespace

void visualize_maze(const Maze& maze) {
    const int cell_size = 24;
    int       rows = maze.rows(), cols = maze.cols();

    // window size
    int width  = cols * cell_size;
    int height = rows * cell_size;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(width),
                                           static_cast<unsigned int>(height)}),
                            "Maze Visualizer");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            // close window
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Fill window

        draw_maze(window, maze);
        window.display();
    }
}