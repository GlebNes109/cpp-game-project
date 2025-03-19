#include "GameSpaceController.cpp"
#include "Structures.h"

#define BOMB_CONTROLLER_H

class BombController {
private:
    std::vector<Bomb>& bombs;
    GameSpaceController& gsc;

public:
    BombController(std::vector<Bomb>& bombs, GameSpaceController& game_space_controller)
    : bombs(bombs), gsc(game_space_controller) {}

    void CheckBombs() {
    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].countdown -= 1;
        if (bombs[i].countdown <= 0) {
            bombs.erase(bombs.begin() + i);
        }
    }
}
    /*void AddBomb(int x, int y) {
        Bomb Bomb;
        Bomb.x = x;
        Bomb.y = y;
        bombs.push_back(Bomb);
    }*/
};