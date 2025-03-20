#include "GameSpaceController.cpp"
#define PLAYER_CONTROLLER_H

class PlayerController {
private:
    GameSpaceController& gsc;

public:
    PlayerController(GameSpaceController& game_space_controller)
    : gsc(game_space_controller) {}
    // стартовая позиция передается в конструктор чтобы было понятно откуда двигать на старте, 
    // новый gsc создавать запрещено, берите его из main по ссылке как это сделано здесь
    // инициализирвоать надо через список, через = ссылка не инициализируется нормально

    void MovePlayer(int y, int x) {
        std::vector<std::string>& space = gsc.getSpace();
        int& playerX = gsc.getPlayerX();
        int& playerY = gsc.getPlayerY();

        int newX = playerX + x;
        int newY = playerY + y;

        // Проверка на стену
        if (space[newY][newX] == ' ') {
            playerX = newX;
            playerY = newY;
        }   
    }
};

