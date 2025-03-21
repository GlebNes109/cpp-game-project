#include "GameSpaceController.h"
#define PLAYER_CONTROLLER_H

class PlayerController {
private:
    GameSpaceController& gsc;
    int bombs_allowed = 2;

public:
    PlayerController(GameSpaceController& game_space_controller);
    
    void MovePlayer(int y, int x);
    int& GetBombsAllowed();
};

