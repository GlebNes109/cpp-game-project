#include "GameSpaceController.cpp"
#define PLAYER_CONTROLLER_H

class PlayerController {
private:
    int playerX, playerY;
    GameSpaceController& gsc;

public:
    PlayerController(int startX, int startY, GameSpaceController& game_space_controller)
    : playerX(startX), playerY(startY), gsc(game_space_controller) {}
    // стартовая позиция передается в конструктор чтобы было понятно откуда двигать на старте, 
    // новый gsc создавать запрещено, берите его из main по ссылке как это сделано здесь
    // инициализирвоать надо через список, через = ссылка не инициализируется нормально

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
    int getPlayerY(); // todo надо доделать геттеры
};

