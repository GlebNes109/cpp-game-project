#include "GameSpaceController.cpp"
#include "Structures.h"

#define BOMB_CONTROLLER_H

class BombController {
private:
    std::vector<Bomb>& bombs;
    GameSpaceController& gsc;

    std::vector<Explosion> explosions;
public:
    BombController(std::vector<Bomb>& bombs, GameSpaceController& game_space_controller)
    : bombs(bombs), gsc(game_space_controller) {}
    void CheckBombs() {
        for (int i = 0; i < bombs.size(); i++) {
            bombs[i].countdown -= 1;
            if (bombs[i].countdown <= 0) {
                Explode(bombs[i]);
                bombs.erase(bombs.begin() + i);
            }
        }
    
    for (int i = 0; i < explosions.size(); i++) {
            explosions[i].timeLeft -= 1;
            if (explosions[i].timeLeft <= 0) {
                explosions.erase(explosions.begin() + i);
            }
        }
    }
    void Explode(const Bomb& bomb) {
        ExplodeDirection(bomb.x, bomb.y, 0, -1);
        ExplodeDirection(bomb.x, bomb.y, 0, 1);
        ExplodeDirection(bomb.x, bomb.y, -1, 0);
        ExplodeDirection(bomb.x, bomb.y, 1, 0);
    }

    void ExplodeDirection(int x, int y, int dx, int dy) {
        while (true) {
            x += dx;
            y += dy;

            if (gsc.getSpace()[y][x] == '#') {
                break;
            }

            explosions.push_back({x, y, 3}); // Взрыв живет 3 секунды
        }
    }
    
            void DrawExplosions() {
        for (const auto& explosion : explosions) {
            mvaddch(explosion.y, explosion.x, '*'); // Отображение взрыва
        }
    }
    /*void AddBomb(int x, int y) {
        Bomb Bomb;
        Bomb.x = x;
        Bomb.y = y;
        bombs.push_back(Bomb);
    }*/
};