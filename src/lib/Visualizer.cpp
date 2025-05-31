#include "Visualizer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <functional>
#include <thread>

#include "Maze.hpp"
#include "MazeGen.hpp"
#include "Utilities.hpp"

// helpers
namespace {

// Draws the maze given a window
void draw_maze(sf::RenderWindow& window, const Maze& maze,
               const ds::Vector<vrtx>& path = {}) {
    // rendering params
    int rows = maze.rows(), cols = maze.cols();

    window.clear(sf::Color::White);

    // draw grid cells
    sf::VertexArray walls(sf::PrimitiveType::Lines);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;

            const Cell& c = maze.cell(i, j);

            sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            rect.setPosition({float(x), float(y)});
            rect.setFillColor(sf::Color::White);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::White);
            window.draw(rect);

            // draw walls
            if (c.top_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(float(x), float(y));
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position = sf::Vector2f(float(x + CELL_SIZE), float(y));
                vertex2.color    = sf::Color::Black;
                walls.append(vertex2);
            }

            if (c.bottom_wall) {
                sf::Vertex vertex;
                vertex.position = sf::Vector2f(float(x), float(y + CELL_SIZE));
                vertex.color    = sf::Color::Black;
                walls.append(vertex);

                sf::Vertex vertex2;
                vertex2.position =
                    sf::Vector2f(float(x + CELL_SIZE), float(y + CELL_SIZE));
                vertex2.color = sf::Color::Black;
                walls.append(vertex2);
            }

            if (c.right_wall) {
                sf::Vertex v1{{float(x + CELL_SIZE), float(y)},
                              sf::Color::Black};
                sf::Vertex v2{{float(x + CELL_SIZE), float(y + CELL_SIZE)},
                              sf::Color::Black};
                walls.append(v1);
                walls.append(v2);
            }

            if (c.left_wall) {
                sf::Vertex v1{{float(x), float(y)}, sf::Color::Black};
                sf::Vertex v2{{float(x), float(y + CELL_SIZE)},
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
            int        cx = path[i].second * CELL_SIZE + CELL_SIZE / 2;
            int        cy = path[i].first * CELL_SIZE + CELL_SIZE / 2;
            sf::Vertex v{{float(cx), float(cy)}, sf::Color::Red};
            solution[i] = v;
        }
        window.draw(solution);
    }
}
};  // namespace

void visualize_maze(const Maze& maze) {
    int rows = maze.rows(), cols = maze.cols();

    // window size
    int width  = cols * CELL_SIZE;
    int height = rows * CELL_SIZE;

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

void visualize_maze_generation(
    Maze&                                                        maze,
    std::function<void(Maze&, std::function<void(const Maze&)>)> generator,
    int start_row, int start_col) {
    int rows = maze.rows(), cols = maze.cols();

    unsigned int width  = static_cast<unsigned int>(cols * CELL_SIZE);
    unsigned int height = static_cast<unsigned int>(rows * CELL_SIZE);

    sf::RenderWindow window(sf::VideoMode({width, height}), "Maze Generator");

    // use def dfs generator if a generator is not provided
    if (!generator) {
        generator = [start_row, start_col](
                        Maze& mz, std::function<void(const Maze&)> on_step) {
            gen_maze_dfs(mz, start_row, start_col, on_step);
        };
    }

    bool running = true;

    auto on_step = [&](const Maze& mz) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
                return;
            }
        }
        draw_maze(window, mz);
        window.display();

        // delay animation
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    };

    generator(maze, on_step);

    while (window.isOpen() && running) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        draw_maze(window, maze);
        window.display();
    }
}
