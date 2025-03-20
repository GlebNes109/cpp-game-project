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


public:
    GameSpaceController(std::vector<Enemy>& enemies, std::vector<Bomb>& bombs, std::vector<Explosion>& explosions)
    : enemies(enemies), bombs(bombs), explosions(explosions) {}
    // std::vector<Enemy> enemies;
    
    char CheckCell(int x, int y) {
        chtype ch = mvinch(y, x);
        return ch & A_CHARTEXT;
    }

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

    bool DrawGameSpace() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                mvaddch(y, x, space[y][x]);
            }
        }
        mvaddch(playerY, playerX, player_symbol);

        for (int enemy = 0; enemy < enemies.size(); enemy++) {
            mvaddch(enemies[enemy].y, enemies[enemy].x, enemies[enemy].symbol);
            if (playerX == enemies[enemy].x and playerY == enemies[enemy].y) {
                return false;
            }
        }

        for (int bomb = 0; bomb < bombs.size(); bomb++) {
            mvaddch(bombs[bomb].y, bombs[bomb].x, bombs[bomb].symbol);
        }

        for (int exp = 0; exp < explosions.size(); exp++) {
            Explosion explosion = explosions[exp];
            bool flag_x_m = false;
            bool flag_x_p = false;
            bool flag_y_m = false;
            bool flag_y_p = false;
            mvaddch(explosion.y, explosion.x, explosion.symbol);
            if (CheckCell(explosion.y, explosion.x) == player_symbol) {
                return false;
            };
            for (int i = 1; i <= explosion.blastRadius; i++) {
                int blast_x_p = explosion.x + i;
                int blast_x_m = explosion.x - i;
                int blast_y_p = explosion.y + i;
                int blast_y_m = explosion.y - i;
    
                // Вправо
                if (blast_x_p >= 0 && blast_x_p < width && !flag_x_p) {
                    int x = blast_x_p;
                    int y = explosion.y;
                    char symbol = CheckCell(x, y);
                    Enemy example_enemy;
                    char symbol_enemy = example_enemy.symbol;
        
                    if (symbol == ' ') {
                        mvaddch(y, x, explosion.symbol);
                    } else if (symbol == symbol_enemy) {
                        for (int enemy = 0; enemy < enemies.size(); enemy++) {
                            if (x == enemies[enemy].x && y == enemies[enemy].y) {
                                enemies.erase(enemies.begin() + enemy);
                                break;
                            }
                        }
                        flag_x_p = true;
                    } else if (symbol == player_symbol) {
                        return false; // игрок умер
                    } else {
                        flag_x_p = true;
                    }
                }
        
                // Влево
                if (blast_x_m >= 0 && blast_x_m < width && !flag_x_m) {
                    int x = blast_x_m;
                    int y = explosion.y;
                    char symbol = CheckCell(x, y);
                    Enemy example_enemy;
                    char symbol_enemy = example_enemy.symbol;
        
                    if (symbol == ' ') {
                        mvaddch(y, x, explosion.symbol);
                    } else if (symbol == symbol_enemy) {
                        for (int enemy = 0; enemy < enemies.size(); enemy++) {
                            if (x == enemies[enemy].x && y == enemies[enemy].y) {
                                enemies.erase(enemies.begin() + enemy);
                                break;
                            }
                        }
                        flag_x_m = true;
                    } else if (symbol == player_symbol) {
                        return false; // игрок умер
                    } else {
                        flag_x_m = true;
                    }
                }
        
                // Вниз
                if (blast_y_p >= 0 && blast_y_p < height && !flag_y_p) {
                    int x = explosion.x;
                    int y = blast_y_p;
                    char symbol = CheckCell(x, y);
                    Enemy example_enemy;
                    char symbol_enemy = example_enemy.symbol;

                    if (symbol == ' ') {
                        mvaddch(y, x, explosion.symbol);
                    } else if (symbol == symbol_enemy) {
                        for (int enemy = 0; enemy < enemies.size(); enemy++) {
                            if (x == enemies[enemy].x && y == enemies[enemy].y) {
                                enemies.erase(enemies.begin() + enemy);
                                break;
                            }
                        }
                        flag_y_p = true;
                    } else if (symbol == player_symbol) {
                        return false; // игрок умер
                    } else {
                        flag_y_p = true;
                    }
                }
        
                // Вверх
                if (blast_y_m >= 0 && blast_y_m < height && !flag_y_m) {
                    int x = explosion.x;
                    int y = blast_y_m;
                    char symbol = CheckCell(x, y);
                    Enemy example_enemy;
                    char symbol_enemy = example_enemy.symbol;
        
                    if (symbol == ' ') {
                        mvaddch(y, x, explosion.symbol);
                    } else if (symbol == symbol_enemy) {
                        for (int enemy = 0; enemy < enemies.size(); enemy++) {
                            if (x == enemies[enemy].x && y == enemies[enemy].y) {
                                enemies.erase(enemies.begin() + enemy);
                                break;
                            }
                        }
                        flag_y_m = true;
                    } else if (symbol == player_symbol) {
                        return false; // игрок умер
                    } else {
                        flag_y_m = true;
                    }
                }
            }
        }
        
        // рефрешить надо в конце иначе из-за постоянной перерисовки картинка будет мерцать
        refresh();
        return true;
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

    char& getPlayerSymbol() {
        return player_symbol;
    }

};

#endif