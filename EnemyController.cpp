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
    // надо чтобы инструкции для врага прописывались тут, а таймер засекался в main, пока не знаю как лучше это сделать
    int it = 0;
    void MoveEnemies() {
        for (int i = 0; i < enemies.size(); i++) {
            int dx = gsc.getPlayerX()- enemies[i].x;
            int dy = gsc.getPlayerY() - enemies[i].y;
        
            int next_x = enemies[i].x;
            int next_y = enemies[i].y;
        
            if (abs(dx) > abs(dy)) { // abs - смотрим расстояние (модуль)
                //  Выбираем какое расстояние больше и туда и идем
                if (dx > 0 && (gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == ' ' || gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == gsc.getPlayerSymbol())) {
                    next_x++;
                } else if (dx < 0 && (gsc.CheckCell(enemies[i].x - 1, enemies[i].y) == ' ' || gsc.CheckCell(enemies[i].x - 1, enemies[i].y) == gsc.getPlayerSymbol())){
                    next_x--;
                } 

                else if (dy > 0 && (gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == ' ' || gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == gsc.getPlayerSymbol())){
                    next_y++;
                } else if (dy < 0 && (gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == ' ' || gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == gsc.getPlayerSymbol())){
                    next_y--;
                }
            } else { // если не пполучилось по модулю то просто двигаем хоть куда-нибудь

                if (dy > 0 && (gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == ' ' || gsc.CheckCell(enemies[i].x, enemies[i].y + 1) == gsc.getPlayerSymbol())) {
                    next_y++;
                } else if (dy < 0 && (gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == ' ' || gsc.CheckCell(enemies[i].x, enemies[i].y - 1) == gsc.getPlayerSymbol())) {
                    next_y--;
                } 

                else if (dx > 0 && (gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == ' ' || gsc.CheckCell(enemies[i].x + 1, enemies[i].y) == gsc.getPlayerSymbol())) {
                    next_x++;
                } else if (dx < 0 && (gsc.CheckCell(enemies[i].x - 1, enemies[i].y) == ' ' || gsc.CheckCell(enemies[i].x - 1, enemies[i].y) == gsc.getPlayerSymbol())) {
                    next_x--;
                }
            }

            enemies[i].x = next_x;
            enemies[i].y = next_y; 
        }
    }

    void AddEnemy(int x, int y) {
        Enemy enemy;
        enemy.x = x;
        enemy.y = y;
        enemies.push_back(enemy);
    }

};
