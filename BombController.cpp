#include "GameSpaceController.cpp"
#include "Structures.h"

#define BOMB_CONTROLLER_H

class BombController {
private:
    std::vector<Bomb>& bombs;
    std::vector<Explosion>& explosions;
    GameSpaceController& gsc;

    public:
    BombController(std::vector<Bomb>& bombs, GameSpaceController& game_space_controller, std::vector<Explosion>& explosions)
    : bombs(bombs), gsc(game_space_controller), explosions(explosions){}
    void CheckBombs() {
        for (int i = 0; i < bombs.size(); i++) {
            bombs[i].countdown -= 1;
            if (bombs[i].countdown <= 0) {
                if (bombs.end() >= bombs.begin() + i) {
                    bombs.erase(bombs.begin() + i);
                    Explosion explosion;
                    explosion.x = bombs[i].x;
                    explosion.y = bombs[i].y;
                    explosion.blastRadius = bombs[i].blastRadius;
                    explosions.push_back(explosion);
                }
            }
        }

        for (int i = 0; i < explosions.size(); i++) {
            explosions[i].countdown--;
            if (explosions[i].countdown <= 0) {
                if (explosions.end() >= explosions.begin() + i) {
                    explosions.erase(explosions.begin() + i);
                }
            }
        }
    }
};