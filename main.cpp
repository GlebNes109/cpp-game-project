#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <chrono>
#include <thread>
#include "GameSpaceController.cpp"
#include "PlayerController.cpp"

int main() {
    initscr(); // для ncurses
    auto time_player = 0.09; // время которое отсекается между нажатиями wasd подобрать по ощущениям
    int startX = 10;
    int startY = 5;
    GameSpaceController gsc;
    PlayerController player(startX, startY, gsc);

    noecho(); // откл отображение вводимых символов и мигающего курсора
    curs_set(0);

    // keypad(stdscr, TRUE); // поддержкf стрелок (не заработало, юзаем wasd пока, потом поправить)

    gsc.DrawGameSpace(startY, startX);
    std::chrono::steady_clock::time_point player_start_time = std::chrono::steady_clock::now();
    while (true) {
        char ch = getch(); // ch - нажатая клавиша
        char tolower(ch); // к нижнему регистру
        // Выход по 'L' (можно поставить любую клавишу чтобы останавливать игру в терминале, жать control c каждый раз не оч удобно просто)
        if (ch == 'l' or ch == 'L') {
            break;
        }
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now(); // текущее время
        std::chrono::duration<double> timer = now - player_start_time; // время с последнего обновления
        if (timer.count() >= time_player) {
            // если прошло n секунд, проверяем клавишу
            if (ch == 'a') {
                player.MovePlayer(0, -1);
                player_start_time = std::chrono::steady_clock::now(); // засечь новый таймер
            }
            if (ch == 'd') {
                player.MovePlayer(0, 1);
                player_start_time = std::chrono::steady_clock::now();
            }
            if (ch == 'w') {
                player.MovePlayer(-1, 0);
                player_start_time = std::chrono::steady_clock::now();
            }
            if (ch == 's') {
                player.MovePlayer(1, 0);
                player_start_time = std::chrono::steady_clock::now();
            }
        }
    }
    endwin(); // конец для ncurses, иначе после работы в терминале останется мусор
    return 0;
}

