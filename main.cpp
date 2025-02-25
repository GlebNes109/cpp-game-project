#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <chrono>
#include <thread>
#include "GameSpaceController.cpp"
#include "PlayerController.cpp"

int main() {
    initscr(); // для ncurses

    int startX = 10;
    int startY = 5;
    GameSpaceController gsc;
    PlayerController player(startX, startY, gsc);

    noecho(); // откл отображение вводимых символов и мигающего курсора
    curs_set(0);

    // keypad(stdscr, TRUE); // поддержкf стрелок (не заработало, юзаем wasd пока, потом поправить)

    gsc.DrawGameSpace(startY, startX);

    while (true) {
        char ch = getch(); // ch - нажатая клавиша
        char tolower(char ch); // к нижнему регистру
        // Выход по 'L' (можно поставить любую клавишу чтобы останавливать игру в терминале, жать control c каждый раз не оч удобно просто)
        if (ch == 'l' or ch == 'L') {
            break;
        }
        // switch case это как if, только оч стильно и модно
        switch (ch) {
            case 'a':
                player.MovePlayer(0, -1); //сейчас в MovePlayer сначала Y, потом X, надо будет переделать
                // std::chrono::milliseconds(10000); сделать задержку (надо придумать что-то чтобы игрок двигался не так быстро, задержка не помогла)
                break; // выход из свичкейса, не из цикла
            case 'd':
                player.MovePlayer(0, 1);
                break;
            case 'w':
                player.MovePlayer(-1, 0);
                break;
            case 's':
                player.MovePlayer(1, 0);
                break;
        }
    }
    endwin(); // конец для ncurses, иначе после работы в терминале останется мусор
    return 0;
}

