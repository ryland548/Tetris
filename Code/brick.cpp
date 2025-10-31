#include <iostream>
#include <SFML/Graphics.hpp>

class Brick {
    public:
        double x = 0.0f;
        double y = 0.0f;
        bool loaded = false;
        float width = 30;
        float height = 30;
        sf::RectangleShape brickShape;
        sf::Color rectangleColor;

    void load() {
        brickShape.setSize(sf::Vector2f(width, height));
        brickShape.setPosition(x, y);
        brickShape.setFillColor(rectangleColor);
    }

    void draw(sf::RenderWindow &window) {
        brickShape.setPosition(x, y);
        window.draw(brickShape);
    }
};
