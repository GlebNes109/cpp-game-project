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
    int blastRadius = 2;
    int countdown = 2;
    char symbol = 'B';
};

struct Explosion {
    int x, y;
    int timeLeft;
    char symbol = '*';
    int blastRadius = 2;
    int countdown = 4;
};

#endif
