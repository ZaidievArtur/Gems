#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

const int PROBABILITY_THRESHOLD_1 = 90;
const int PROBABILITY_THRESHOLD_2 = 95;
const int textureWidth = 49;

Game::Game() :
        window(sf::VideoMode(740, 480), "Let's play!"),
        click(0), isSwap(false), isMoving(false) {
    srand(time(0));
    window.setFramerateLimit(200);
    loadResources();
    initGrid();
}

void Game::loadResources() {
    if (!textureGems.loadFromFile("C:/Users/User/CLionProjects/Gems/Image/Gems.png") ||
        !textureSky.loadFromFile("C:/Users/User/CLionProjects/Gems/Image/cloud3.jpg")) {
        throw std::runtime_error("Failed to load textures");
    }

    gems.setTexture(textureGems);
    gamingBackGround.setTexture(textureSky);

    sf::Image icon;
    if (!icon.loadFromFile("C:/Users/User/CLionProjects/Gems/Image/icon.png")) {
        throw std::runtime_error("Failed to load icon");
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
}

void Game::initGrid() {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++){
            grid[i][j].kind = rand() % 5;
            grid[i][j].row = i;
            grid[i][j].col = j;
            grid[i][j].y = i * ts;
            grid[i][j].x = j * ts;
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::checkNeighboring() {
    if (abs(x - x0) + abs(y - y0) == 1) {
        swap(grid[y0][x0], grid[y][x]);
        isSwap = true;
        click = 0;
    } else {
        click = 1;
    }
}

void Game::processClick() {
    click++;
    if (click == 1) {
        x0 = pos.x / ts + 1;
        y0 = pos.y / ts + 1;
    } else if (click == 2) {
        x = pos.x / ts + 1;
        y = pos.y / ts + 1;
        checkNeighboring();
        click = 0;
    }
}


void Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!isSwap && !isMoving) {
                pos = sf::Mouse::getPosition(window) - offset;
                processClick();
            }
        }
    }
}

void Game::update() {
    int score = 0;
    findMatches(score);
    moveTiles(score);
    updateGrid();
}

void Game::render() {
    window.draw(gamingBackGround);

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            Tile p = grid[i][j];
            gems.setTextureRect(sf::IntRect(p.kind * textureWidth, 0, textureWidth, textureWidth));
            gems.setPosition(p.x, p.y);
            gems.move(offset.x - ts, offset.y - ts);
            window.draw(gems);
        }
    }

    window.display();
}

void Game::swap(Tile p1, Tile p2) {
    std::swap(p1.col, p2.col);
    std::swap(p1.row, p2.row);

    grid[p1.row][p1.col] = p1;
    grid[p2.row][p2.col] = p2;
}

void Game::findMatches(int score) {
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if (grid[i][j].kind == grid[i + 1][j].kind &&
                grid[i][j].kind == grid[i - 1][j].kind) {
                for (int n = -1; n <= 1; n++) grid[i + n][j].match++;
            }
            if (grid[i][j].kind == grid[i][j + 1].kind &&
                grid[i][j].kind == grid[i][j - 1].kind) {
                for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
                if (grid[i][j].match == 1) {
                    grid[i][j + 1].match == 1;
                }
            }
            score += grid[i][j].match;
        }
    }

    if (isSwap && !isMoving) {
        if (std::all_of(&grid[0][0], &grid[0][0] + 100, [](const Tile& t) { return t.match == 0; })) {
            swap(grid[y0][x0], grid[y][x]);
        }
        isSwap = false;
    }
}

void Game::moveTiles(int score) {
    isMoving = false;
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            Tile& p = grid[i][j];
            int dx = p.x - p.col * ts;
            int dy = p.y - p.row * ts;
            if (dx) p.x -= dx / std::abs(dx);
            if (dy) p.y -= dy / std::abs(dy);
            if (dx || dy) isMoving = true;
        }
    }
    if (isSwap && !isMoving) { // Если нет совпадений
        if (!score) swap(grid[y0][x0], grid[y][x]);
        isSwap = false;
    }
}

void Game::updateGrid() {
    if (!isMoving) {
        for (int j = 1; j < 9; j++) {
            int emptyRow = 8;
            for (int i = 8; i > 0; i--) {
                if (!grid[i][j].match) {
                    while (emptyRow > 0 && grid[emptyRow][j].match) {
                        emptyRow--;
                    }
                    if (emptyRow > 0) {
                        swap(grid[i][j], grid[emptyRow][j]);
                        emptyRow--;
                    }
                }
            }
        }

        for (int i = 9; i > 0; i--) {
            for (int j = 1; j < 9; j++) {
                if (grid[i][j].match) {
                    Bonus* bonus;
                    int meter = rand() % 100;
                    if (meter > PROBABILITY_THRESHOLD_2) {
                        bonus = new Recolor();
                    } else if (meter > PROBABILITY_THRESHOLD_1) {
                        bonus = new Bomb();
                    } else {
                        bonus = new Default();
                    }
                    bonus->apply(grid[i][j], grid);
                    delete bonus;
                }
            }
        }
    }
}
