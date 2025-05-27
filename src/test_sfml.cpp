#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <cstddef>

/// Generates a simple star
sf::ConvexShape gen_star(float cx, float cy, float outer_rad, float inner_rad,
                         std::size_t points = 5) {
    sf::ConvexShape star(points * 2);

    float angle_step = float(M_PI / points);
    float angle      = -M_PI / 2;

    for (int i = 0; i < points; ++i) {
        float r = (i % 2 == 0) ? outer_rad : inner_rad;
        float x = cx + std::cos(angle) * r;
        float y = cy + std::sin(angle) * r;
        star.setPoint(i, {x, y});
        angle += angle_step;
    }

    star.setFillColor(sf::Color::Green);
    return star;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Test WIndow");

    auto star = gen_star(400.f, 300.f, 100.f, 45.f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            // Close the window if requested
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Fill the window with a dark gray color
        window.clear(sf::Color(30, 30, 30));
        window.draw(star);
        window.display();
    }

    return 0;
}
