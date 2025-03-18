#ifndef GAME_SPACE_CONTROLLER_H
#define GAME_SPACE_CONTROLLER_H

#include <vector>
#include <string>
#include "Structures.h"
#include <ncurses.h>

class GameSpaceController {
private:
    int height = 11;
    int width = 21;
    int playerX = 5;
    int playerY = 10;
    std::vector<Enemy>& enemies;
    std::vector<Bomb>& bombs;
    std::vector<std::string> space;

public:
    GameSpaceController(std::vector<Enemy>& enemies, std::vector<Bomb>& bombs);
    
    void AddEnemy(int x, int y);
    void DrawGameSpace();
    std::vector<std::string>& getSpace();
    int& getPlayerX();
    int& getPlayerY();
};

#endif
