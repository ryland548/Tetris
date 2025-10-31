#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include "./Code/brick.cpp"
#include "./Code/startScreen.cpp"
#include "./Code/deadScreen.cpp"
#include "./Code/score.cpp"

void drawGrid(std::vector<std::vector<int>> &grid, int gridHeight, int gridWidth, std::vector<Brick> &bricks) {
    bricks.clear();
    for (int i = 0; i < gridHeight; i += 1) {
        for (int j = 0; j < gridWidth; j += 1) {
            Brick brick = Brick();
            if (grid[i][j] == 1) {
                brick.rectangleColor = sf::Color::Red;
            } else if (grid[i][j] == 2) {
                brick.rectangleColor = sf::Color::Green;
            } else if (grid[i][j] == 3) {
                brick.rectangleColor = sf::Color::Blue;
            } else if (grid[i][j] == 4) {
                sf::Color purple = sf::Color(128, 0, 128);
                brick.rectangleColor = purple;
            } else if (grid[i][j] == 5) {
                brick.rectangleColor = sf::Color::Yellow;
            } else {
                brick.rectangleColor = sf::Color::Black;
            }
            brick.x = (j * 36) + 12;
            brick.y = (i * 36) + 7;
            brick.load();
            bricks.push_back(brick);
        }
    }
}

int main() {
    std::vector<std::vector<std::vector<int>>> tetrisPieces = {
        {{1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}},
        {{1, 8}, {1, 9}, {1, 10}, {1, 11}},
        {{1, 8}, {1, 9}, {1, 10}},
        {{1, 7}, {1, 8}, {1, 9}, {2, 9}, {2, 10}, {2, 11}},
        {{1, 8}, {1, 9}, {2, 8}, {2, 9}},
        {{1, 8}, {2, 8}, {2, 9}, {3, 9}},
        {{1, 9}, {2, 9}, {3, 9}, {3, 10}},
        {{1, 7}, {2, 8}, {1, 8}, {2, 9}, {2, 10}, {1, 10}},
        {{1, 7}, {1, 8}, {1, 9}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}},
        {{1, 9}, {2, 9}, {2, 8}, {2, 10}, {3, 9}},
        {{1, 9}, {1, 10}, {2, 9}, {2, 10}, {3, 10}},
        {{1, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {4, 10}},
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    const int gridWidth = 19;
    const int gridHeight = 22;
    std::vector<Brick> bricks;
    std::vector<std::vector<int>> grid;
    int scoreNum = 0;
    for (int i = 0; i < gridHeight; i += 1) {
        std::vector<int> collumn;
        for (int j = 0; j < gridWidth; j += 1) {
            collumn.push_back(0);
        }
        grid.push_back(collumn);
    }
    sf::Music music;
    if (!music.openFromFile("./Assets/Audio/tetris.wav")) {
        std::cerr << "could not load music" << std::endl;
    }
    music.setLoop(true);
    music.setVolume(30);
    music.play();

    StartScreen startScreen = StartScreen();
    startScreen.load();
    Score score = Score();
    score.load();
    DeadScreen deadScreen = DeadScreen();
    deadScreen.load();
    bool dead = false;
    bool start = false;
    bool tetrisPieceActive = false;
    sf::RenderWindow window(sf::VideoMode(700, 800), "Tetris");
    std::vector<std::vector<int>> currentPieceIndexs;
    int currentPieceColor = 1;
    sf::Clock tickClock;
    sf::Clock scoreClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A && tetrisPieceActive) {
                    if (!start) {
                        start = true;
                    }
                    bool canMoveLeft = true;
                    for (std::vector<int> &brickPositions : currentPieceIndexs) {
                        grid[brickPositions[0]][brickPositions[1]] = 0;
                    }
                    for (auto &brickPositions : currentPieceIndexs) {
                        int y = brickPositions[0];
                        int x = brickPositions[1];
                        if (x - 1 < 0 || grid[y][x - 1] != 0) {
                            canMoveLeft = false;
                            break;
                        }
                    }
                    for (auto &brickPositions : currentPieceIndexs) {
                        grid[brickPositions[0]][brickPositions[1]] = currentPieceColor;
                    }
                    if (canMoveLeft) {
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            grid[brickPositions[0]][brickPositions[1]] = 0;
                        }
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            brickPositions[1] -= 1;
                        }
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            grid[brickPositions[0]][brickPositions[1]] = currentPieceColor;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::D && tetrisPieceActive) {
                    bool canMoveRight = true;
                    if (!start) {
                        start = true;
                    }
                    for (std::vector<int> &brickPositions : currentPieceIndexs) {
                        grid[brickPositions[0]][brickPositions[1]] = 0;
                    }
                    for (auto &brickPositions : currentPieceIndexs) {
                        int y = brickPositions[0];
                        int x = brickPositions[1];
                        if (x + 1 >= gridWidth || grid[y][x + 1] != 0) {
                            canMoveRight = false;
                            break;
                        }
                    }
                    for (auto &brickPositions : currentPieceIndexs) {
                        grid[brickPositions[0]][brickPositions[1]] = currentPieceColor;
                    }
                    if (canMoveRight) {
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            grid[brickPositions[0]][brickPositions[1]] = 0;
                        }
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            brickPositions[1] += 1;
                        }
                        for (std::vector<int> &brickPositions : currentPieceIndexs) {
                            grid[brickPositions[0]][brickPositions[1]] = currentPieceColor;
                        }
                    }
                }
            }
        }
        window.clear();
        if (!tetrisPieceActive and !dead) {
            bool canSpawn = true;
            int randomPieceIndex = rand() % tetrisPieces.size();
            std::vector<std::vector<int>> currentPiece = tetrisPieces[randomPieceIndex];
            for (std::vector<int> &brickPositions : currentPiece) {
                int y = brickPositions[0];
                int x = brickPositions[1];
                if (grid[y][x] != 0) {
                    canSpawn = false;
                    break;
                }
                std::uniform_int_distribution<> distrib(1, 5);
                currentPieceColor = distrib(gen);
                grid[y][x] = currentPieceColor;
            }
            if (!canSpawn) {
                dead = true;
            }
            tetrisPieceActive = true;
            currentPieceIndexs = currentPiece;
        }
        sf::Time scoreClockElapsed = scoreClock.getElapsedTime();
        if (scoreClockElapsed.asSeconds() >= 1 && start && !dead) {
            scoreNum += 1;
            scoreClock.restart();
        }
        sf::Time tickClockElapsed = tickClock.getElapsedTime();
        if (tickClockElapsed.asSeconds() >= 0.2 && start && !dead) {
            if (tetrisPieceActive) {
                bool canMoveDown = true;
                for (std::vector<int> &brickPositions : currentPieceIndexs) {
                     grid[brickPositions[0]][brickPositions[1]] = 0;
                }
                for (std::vector<int> &brickPositions : currentPieceIndexs) {
                    int y = brickPositions[0];
                    int x = brickPositions[1];
                    if (y + 1 >= gridHeight || grid[y + 1][x] != 0) {
                        canMoveDown = false;
                        break;
                    }
                }
                if (canMoveDown) {
                    for (std::vector<int> &brickPositions : currentPieceIndexs) {
                        brickPositions[0] += 1;
                    }
                } else {
                    tetrisPieceActive = false;
                }
                for (std::vector<int> &brickPositions : currentPieceIndexs) {
                    grid[brickPositions[0]][brickPositions[1]] = currentPieceColor;
                }
                tickClock.restart();
            }
        }
        for (std::vector<int> &gridColumn: grid) {
            bool fullGridRow = true;
            for (int &cellValue: gridColumn) {
                if (cellValue == 0) {
                    fullGridRow = false;
                }
            }
            if (fullGridRow) {
                for (int &cellValue: gridColumn) {
                    cellValue = 0;
                }
                scoreNum += 100;
            }
        }
        drawGrid(grid, gridHeight, gridWidth, bricks);
        for (Brick &brick : bricks) {
            brick.draw(window);
        }
        if (!start) {
            startScreen.draw(window);
        }
        if (dead) {
            for (std::vector<int> &gridColumn: grid) {
                for (int &cellValue: gridColumn) {
                    cellValue = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                for (std::vector<int> &gridColumn: grid) {
                    for (int &cellValue: gridColumn) {
                        cellValue = 0;
                    }
                }
                dead = false;
                start = false;
                scoreNum = 0;
                tetrisPieceActive = false;
                currentPieceIndexs.clear();
                scoreNum = 0;
                tickClock.restart();
                scoreClock.restart();
            }
            deadScreen.draw(window);
        }
        score.draw(window, scoreNum);
        window.display();
    }
    return 0;
}
