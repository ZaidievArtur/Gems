#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Bonus.h"

class Game {
public:
    Game();
    void run();

private:
    void loadResources();
    void initGrid();
    void handleEvents();
    void update();
    void render();
    void swap(Tile p1, Tile p2);
    void findMatches(int score);
    void moveTiles(int score);
    void updateGrid();

    const int ts = 54; // tile size
    const sf::Vector2i offset = sf::Vector2i(48, 24);

    sf::RenderWindow window;
    sf::Texture textureGems, textureSky;
    sf::Sprite gems, gamingBackGround;
    Tile grid[10][10];

    int x0, y0, x, y;
    int click;
    sf::Vector2i pos;
    bool isSwap, isMoving;
};

#endif // GAME_H
