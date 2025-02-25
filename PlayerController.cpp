#include "GameSpaceController.cpp"
#define PLAYER_CONTROLLER_H

class PlayerController {
private:
    int playerX, playerY;
    GameSpaceController gsc;

public:
    PlayerController(int startX, int startY, GameSpaceController game_space_controller) {
        playerX = startX;
        playerY = startY; 
        gsc = game_space_controller; //инициализация того что пришло в конструктор #этовамнепитон)))
    };
    // стартовая позиция передается в конструктор чтобы было понятно откуда двигать на старте, gsc передается 
    // потому что новый локально делать нельзя (может можно я хз), я думаю могут быть проблемы

    void MovePlayer(int y, int x) {
        std::vector<std::string>& space = gsc.getSpace();
        int newX = playerX + x;
        int newY = playerY + y;

        // Проверка на стену
        if (space[newY][newX] == ' ') {
            playerX = newX;
            playerY = newY;
            gsc.DrawGameSpace(playerY, playerX);
        }
    
    }
    int getPlayerX();
    int getPlayerY();
};

