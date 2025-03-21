#ifndef GAME_SPACE_CONTROLLER_H
#define GAME_SPACE_CONTROLLER_H

#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include "Structures.h"

class GameSpaceController {
private:
    int playerX = 10;
    int playerY = 5;
    char player_symbol = 'P';
    std::vector<Enemy>& enemies;
    std::vector<Bomb>& bombs;
    std::vector<Explosion>& explosions;
    std::vector<std::string> space = {
        "#####################",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "#####################"
    };
    int height = space.size();
    int width = space[0].size();

public:
    GameSpaceController(std::vector<Enemy>& enemies, std::vector<Bomb>& bombs, std::vector<Explosion>& explosions);
    char CheckCell(int x, int y);

    void AddEnemy(int x, int y);
    void AddBomb(int x, int y);
    bool DrawGameSpace();

    std::vector<std::string>& getSpace();
    int& getPlayerX();
    int& getPlayerY();
    char& getPlayerSymbol();
};

#endif
