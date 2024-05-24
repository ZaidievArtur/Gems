#include "Bonus.h"

void Bonus::applyBonus(Tile grid[10][10], int i, int j, int& n, int ts) {
    int meter = rand() % 100;
    if (meter > 90) {
        int randx = rand() % 4;
        int randy = rand() % 4;
        int randx2 = rand() % 4;
        int randy2 = rand() % 4;
        int prev = 0;

        if (meter > 95) {
            prev = grid[i][j].kind;
            grid[i][j].kind = 5;
            grid[i][j].y = -ts * n++;
            grid[i][j].match = 1;
            if (randx + i <= 7) {
                if (randy + j <= 7) grid[randx + i][randy + j].kind = prev;
                else grid[randx + i][randy - j].kind = prev;
            } else {
                if (randy + j <= 7) grid[randx - i][randy + j].kind = prev;
                else grid[randx - i][randy - j].kind = prev;
            }
            if (randx2 + i <= 7) {
                if (randy2 + j <= 7) grid[randx2 + i][randy2 + j].kind = prev;
                else grid[randx2 + i][randy2 - j].kind = prev;
            } else {
                if (randy2 + j <= 7) grid[randx2 - i][randy2 + j].kind = prev;
                else grid[randx2 - i][randy2 - j].kind = prev;
            }
        } else {
            grid[i][j].kind = 6;
            grid[i][j].y = -ts * n++;
            grid[i][j].match = 1;

            for (int k = 0; k < 5; ++k) {
                int randx3 = rand() % 8;
                int randy3 = rand() % 8;
                grid[randx3][randy3].match = 1;
            }
        }
    } else {
        grid[i][j].kind = rand() % 5;
        grid[i][j].y = -ts * n++;
        grid[i][j].match = 0;
    }
}
