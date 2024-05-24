#ifndef BONUS_H
#define BONUS_H

#include "Tile.h"
#include <cstdlib>

class Bonus {
public:
    static void applyBonus(Tile grid[10][10], int i, int j, int& n, int ts);
};

#endif // BONUS_H
