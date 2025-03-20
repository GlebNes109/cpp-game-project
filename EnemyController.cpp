#include "GameSpaceController.cpp"
#include "Structures.h"

#define PLAYER_CONTROLLER_H

class EnemyController {
private:
    std::vector<Enemy>& enemies;
    GameSpaceController& gsc;

public:
    EnemyController(std::vector<Enemy>& enemies, GameSpaceController& game_space_controller)
    : enemies(enemies), gsc(game_space_controller) {}
    std::vector<char> enemy_instruction_0 = {'w', 'w', 'w', 'w', 's', 's', 's', 's'};
    std::vector<std::vector<char>> instructions = {enemy_instruction_0};
    // надо чтобы инструкции для врага прописывались тут, а таймер засекался в main, пока не знаю как лучше это сделать
    int it = 0;
    void MoveEnemies() {
        for (int i = 0; i < enemies.size(); i++) {
            int dx = gsc.getPlayerX()- enemies[i].x;
            int dy = gsc.getPlayerY() - enemies[i].y;
        
            int next_x = enemies[i].x;
            int next_y = enemies[i].y;
        
            if (abs(dx) > abs(dy)) { // abs - смотрим расстояние (модуль)
                // Пробуем двигаться по X если по x дальше от игрока
                if (dx > 0 && gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == ' ') {
                    next_x++;
                } else if (dx < 0 && gsc.CheckCell(enemies[i].x - 1, enemies[i].y) == ' '){
                    next_x--;
                } 
                // Если не получилось по X пробуем по Y
                else if (dy > 0 && gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == ' '){
                    next_y++;
                } else if (dy < 0 && gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == ' '){
                    next_y--;
                }
            } else { // если не пполучилось по модулю то просто двигаем хоть куда-нибудь

                if (dy > 0 && gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == ' ') {
                    next_y++;
                } else if (dy < 0 && gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == ' ') {
                    next_y--;
                } 

                else if (dx > 0 && gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == ' ') {
                    next_x++;
                } else if (dx < 0 && gsc.CheckCell (enemies[i].x - 1, enemies[i].y) == ' ') {
                    next_x--;
                }
            }

            enemies[i].x = next_x;
            enemies[i].y = next_y; 
        }


        /*if (it < instructions[enemy_id].size()) {
            it++;
        } else {
            it = 0;
        }
        char command = instructions[enemy_id][it];
        if (command == 'w') {
            enemies[enemy_id].y+=1;
        }
        if (command == 'a') {
            enemies[enemy_id].x-=1;
        }
        if (command == 's') {
            enemies[enemy_id].y-=1;
        }
        if (command == 'd') {
            enemies[enemy_id].x+=1;
        }*/
    }

};
