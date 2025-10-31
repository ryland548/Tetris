#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Score {
    public:
        int score = 0;
        int x = 70;
        int y = 70;
        float fontSize = 100;
        std::string fontPath = "./Assets/Fonts/font.ttf";
        sf::Font font;
        sf::Text text;

    void load() {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Error loading Score Font.\n";
        }
        text.setFont(font);
        text.setString(std::to_string(score));
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window, int changedscore) {
        if (changedscore != score) {
            score = changedscore;
        }
        text.setString(std::to_string(score));
        window.draw(text);
    }
};
