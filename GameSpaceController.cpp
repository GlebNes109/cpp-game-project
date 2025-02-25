#ifndef GAME_SPACE_CONTROLLER_H // защита от повторной компиляции (без заголовочных файлов тяжело)

#define GAME_SPACE_CONTROLLER_H // отдельных заголовочных файлов пока нет (я не оч понял зачем они нужны), работает и без них

#include <iostream>
#include <string>
#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <vector>


class GameSpaceController {
private:
    int height = 11;
    int width = 21;
    std::vector<std::string> space = {
        "#####################",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "# # # # # # # # # # #",
        "#                   #",
        "#####################"
    };

public:
    
    void DrawGameSpace(int playerY, int playerX) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                mvaddch(y, x,  space[y][x]);
                mvaddch(playerY, playerX, 'P');
            }
        }
        // рефрешить надо в конце иначе из-за постоянной перерисовки картинка будет мерцать
        refresh();
    }

    /*void DrawPlayer(int playerY, int playerX) {
        mvaddch(playerY, playerX, 'P');
        refresh();
    }*/

    std::vector<std::string>& getSpace() {
        return space;
    }
    // сейчас возвращается ссылка на space, это чтобы возвращалось актуальное пространство которое можно менять извне.
    // менять извне space лучше не надо (для этого собственно и есть GameSpaceController), но такая возможность на всякий случай есть
};

#endif