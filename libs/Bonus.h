#ifndef BONUS_H
#define BONUS_H

#include "Tile.h"
#include <cstdlib>

class Bonus {
public:
    virtual void apply(Tile& tile, Tile grid[10][10]) = 0;
    virtual ~Bonus() = default;
};

class Recolor : public Bonus {
public:
    void apply(Tile& tile, Tile grid[10][10]) override;
};

class Bomb : public Bonus {
public:
    void apply(Tile& tile, Tile grid[10][10]) override;
};

class Default : public Bonus {
public:
    void apply(Tile& tile, Tile grid[10][10]) override;
};

#endif // BONUS_H
