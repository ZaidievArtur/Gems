#ifndef TILE_H
#define TILE_H

const int ts = 54; // tile size


class Tile {
public:
    int x, y, col, row, kind, match;

    Tile() : match(0) {}
};

#endif // TILE_H
