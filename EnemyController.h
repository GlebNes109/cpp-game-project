#include "GameSpaceController.h"
#include "Structures.h"

#define PLAYER_CONTROLLER_H

class EnemyController {
private:
    std::vector<Enemy>& enemies;
    GameSpaceController& gsc;

public:
    EnemyController(std::vector<Enemy>& enemies, GameSpaceController& game_space_controller);
    void MoveEnemies();
    void AddEnemy(int x, int y);
};