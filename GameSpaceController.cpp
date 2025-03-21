#include "GameSpaceController.h"

GameSpaceController::GameSpaceController(std::vector<Enemy>& enemies, std::vector<Bomb>& bombs, std::vector<Explosion>& explosions)
: enemies(enemies), bombs(bombs), explosions(explosions) {}

char GameSpaceController::CheckCell(int x, int y) {
    chtype ch = mvinch(y, x);
    return ch & A_CHARTEXT;
}

void GameSpaceController::AddEnemy(int x, int y){
    Enemy enemy;
    enemy.x = x;
    enemy.y = y;
    enemies.push_back(enemy);
}

void GameSpaceController::AddBomb(int x, int y) {
    Bomb Bomb;
    Bomb.x = x;
    Bomb.y = y;
    bombs.push_back(Bomb);
}

bool GameSpaceController::DrawGameSpace() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            attron(COLOR_PAIR(3) | A_DIM);
            mvaddch(y, x, space[y][x]);
            attroff(COLOR_PAIR(3) | A_DIM);
        }
    }

    attron(COLOR_PAIR(2));
    mvaddch(playerY, playerX, player_symbol);
    attroff(COLOR_PAIR(2));

    for (int enemy = 0; enemy < enemies.size(); enemy++) {
        attron(COLOR_PAIR(1));
        mvaddch(enemies[enemy].y, enemies[enemy].x, enemies[enemy].symbol);
        attroff(COLOR_PAIR(1));
        if (playerX == enemies[enemy].x and playerY == enemies[enemy].y) {
            return false;
        }
    }

    for (int bomb = 0; bomb < bombs.size(); bomb++) {
        attron(COLOR_PAIR(4));
        mvaddch(bombs[bomb].y, bombs[bomb].x, bombs[bomb].symbol);
        attroff(COLOR_PAIR(4));
    }

    attron(COLOR_PAIR(4));
    for (int exp = 0; exp < explosions.size(); exp++) {
        // отрисовка взрывов с проверкой, есть ли стена, есть ли враг и тд
        Explosion explosion = explosions[exp];
        bool flag_x_m = false;
        bool flag_x_p = false;
        bool flag_y_m = false;
        bool flag_y_p = false;
        if (explosion.y == playerY && explosion.x == playerX) {
            return false;
        };
        mvaddch(explosion.y, explosion.x, explosion.symbol);
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
                Enemy example_enemy; // чтобы достать символ врага из структуры
                char symbol_enemy = example_enemy.symbol;
                
                if (symbol == ' ') {
                    mvaddch(y, x, explosion.symbol);
                } else if (symbol == symbol_enemy) {
                    for (int enemy = 0; enemy < enemies.size(); enemy++) { // если взрыв задел врага, вычисляем по циклу какой именно это был враг
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
    attroff(COLOR_PAIR(4));

    
    // рефрешить надо в конце иначе из-за постоянной перерисовки картинка будет мерцать
    refresh();
    return true;
}

std::vector<std::string>& GameSpaceController::getSpace() {
    return space; // подумать, возвращать только space или space + обьекты на нем
}

int& GameSpaceController::getPlayerX() {
    return playerX;
}

int& GameSpaceController::getPlayerY() {
    return playerY;
}

char& GameSpaceController::getPlayerSymbol() {
    return player_symbol;
}