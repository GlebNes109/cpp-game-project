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
    void MoveEnemy(int enemy_id) {
        if (it < instructions[enemy_id].size()) {
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
        }        
    }

};
