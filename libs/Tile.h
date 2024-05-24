#ifndef TILE_H
#define TILE_H

class Tile {
public:
    int x, y, col, row, kind, match, alpha;

    Tile() : match(0), alpha(255) {}
};

#endif // TILE_H
