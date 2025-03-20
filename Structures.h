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
    int blastRadius;
    int countdown = 3;
    char symbol = 'B';
};

struct Explosion {
        int x, y;
        int timeLeft;
    };

#endif
