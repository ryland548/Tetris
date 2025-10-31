#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StartScreen {
    public:
        int x = 60;
        int y = 500;
        float fontSize = 60;
        std::string fontPath = "./Assets/Fonts/font.ttf";
        sf::Font font;
        sf::Text text;

    void load() {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Error loading Score Font.\n";
        }
        text.setFont(font);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
        text.setString("Move Block to start (WASD )");
    }

    void draw(sf::RenderWindow &window) {
        window.draw(text);
    }
};
