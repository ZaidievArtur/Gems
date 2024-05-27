#include "Bonus.h"

namespace {
    const int BONUS_TYPE_1 = 5;
    const int BONUS_TYPE_2 = 6;
    const int PROBABILITY_THRESHOLD_1 = 90;
    const int PROBABILITY_THRESHOLD_2 = 95;
    const int GRID_SIZE = 10;
    const int MAX_RANDOM_POSITION = 4;
    const int RANDOM_MATCH_COUNT = 5;
}

void Recolor::apply(Tile& tile, Tile grid[GRID_SIZE][GRID_SIZE]) {
    int prev = tile.kind;
    tile.kind = BONUS_TYPE_1;
    tile.y = -ts;
    tile.match = 1;

    auto updateKind = [&](int dx, int dy) {
        if (tile.row + dx < GRID_SIZE && tile.row + dx >= 0 && tile.col + dy < GRID_SIZE && tile.col + dy >= 0) {
            grid[tile.row + dx][tile.col + dy].kind = prev;
        }
    };

    updateKind(rand() % MAX_RANDOM_POSITION, rand() % MAX_RANDOM_POSITION);
    updateKind(rand() % MAX_RANDOM_POSITION, rand() % MAX_RANDOM_POSITION);
}

void Bomb::apply(Tile& tile, Tile grid[GRID_SIZE][GRID_SIZE]) {
    tile.kind = BONUS_TYPE_2;
    tile.y = -ts;
    tile.match = 1;

    for (int k = 0; k < RANDOM_MATCH_COUNT; ++k) {
        int randx = rand() % (GRID_SIZE - 2);
        int randy = rand() % (GRID_SIZE - 2);
        grid[randx][randy].match = 1;
    }
}

void Default::apply(Tile& tile, Tile grid[GRID_SIZE][GRID_SIZE]) {
    tile.kind = rand() % 5;
    tile.y = -ts;
    tile.match = 0;
}
