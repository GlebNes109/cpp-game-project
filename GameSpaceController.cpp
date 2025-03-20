#ifndef GAME_SPACE_CONTROLLER_H // защита от повторной компиляции (без заголовочных файлов тяжело)

#define GAME_SPACE_CONTROLLER_H // отдельных заголовочных файлов пока нет (я не оч понял зачем они нужны), работает и без них

#include <iostream>
#include <string>
#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <vector>
#include "Structures.h"

class GameSpaceController {
private:
    int height = 11;
    int width = 21;
    int playerX = 10;
    int playerY = 10;
    std::vector<Enemy>& enemies;
    std::vector<Bomb>& bombs;
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


public:
    GameSpaceController(std::vector<Enemy>& enemies, std::vector<Bomb>& bombs)
    : enemies(enemies), bombs(bombs) {}
    // std::vector<Enemy> enemies;
    
    void AddEnemy(int x, int y){
        Enemy enemy;
        enemy.x = x;
        enemy.y = y;
        enemies.push_back(enemy);
    }
    
    void AddBomb(int x, int y) {
        Bomb Bomb;
        Bomb.x = x;
        Bomb.y = y;
        bombs.push_back(Bomb);
    }

    void DrawGameSpace() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                mvaddch(y, x, space[y][x]);
            }
        }
        mvaddch(playerY, playerX, 'P');
        for (int enemy = 0; enemy < enemies.size(); enemy++) {
            mvaddch(enemies[enemy].y, enemies[enemy].x, enemies[enemy].symbol);
            refresh();
        }

        for (int bomb = 0; bomb < bombs.size(); bomb++) {
            mvaddch(bombs[bomb].y, bombs[bomb].x, bombs[bomb].symbol);
            refresh();
        }
        // рефрешить надо в конце иначе из-за постоянной перерисовки картинка будет мерцать
        refresh();
    }

    std::vector<std::string>& getSpace() {
        return space; // подумать, возвращать только space или space + обьекты на нем
    }

    int& getPlayerX() {
        return playerX;
    }
    int& getPlayerY() {
        return playerY;
    }
    // сейчас возвращается ссылка на space, это чтобы возвращалось актуальное пространство которое можно менять извне.
    // менять извне space лучше не надо (для этого собственно и есть GameSpaceController), но такая возможность на всякий случай есть
};

#endif