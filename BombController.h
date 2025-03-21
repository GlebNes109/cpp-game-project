#include "GameSpaceController.h"
#include "Structures.h"

#define BOMB_CONTROLLER_H

class BombController {
private:
    std::vector<Bomb>& bombs;
    std::vector<Explosion>& explosions;
    GameSpaceController& gsc;

    public:
    BombController(std::vector<Bomb>& bombs, GameSpaceController& game_space_controller, std::vector<Explosion>& explosions);
    void CheckBombs();
};