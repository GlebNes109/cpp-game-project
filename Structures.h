#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Enemy {
    int x;
    int y;
    char symbol = 'E';
};

struct Bomb {
    int x;
    int y;
    char symbol = 'B';
};

#endif
