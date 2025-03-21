#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Enemy {
    int x;
    int y;
    char symbol = 'E';
    long long enemy_id;
};

struct Bomb {
    int x;
    int y;
    int blastRadius = 2;
    int countdown = 5;
    char symbol = 'B';
};

struct Explosion {
    int x, y;
    int timeLeft;
    char symbol = '*';
    int blastRadius = 2;
    int countdown = 2;
};

#endif
