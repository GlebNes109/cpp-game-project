#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <chrono>
#include <thread>
#include "GameSpaceController.cpp"
#include "PlayerController.cpp"
#include "Structures.h"
#include "EnemyController.cpp"
#include "BombController.cpp"


int main() {
    initscr(); // для ncurses
    // nodelay(stdscr, TRUE); // это чтобы getch не блокировал выполнение
    // timeout(0);
    auto time_player = 0.09; // время которое отсекается между нажатиями wasd подобрать по ощущениям
    int startX = 10;
    int startY = 5;
    std::vector<Enemy> enemies; // по архитектуре надо будет уточнить, но скорее всего так будет норм
    std::vector<Bomb> bombs;
    // списки врагов, бомб итд создаются тут, потом закидываем ссылки тому кому они нужны
    // EnemyController enemycon(enemies, gsc);

    GameSpaceController gsc(enemies, bombs); // ВНИМАНИЕ, это должно быть единственное место где инициализирвоан gsc, повторная инициализация = потеря игрового поля
    BombController bombcon(bombs, gsc);
    EnemyController enemycon(enemies, gsc);

    PlayerController player(gsc);
    noecho(); // откл отображение вводимых символов и мигающего курсора
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    gsc.AddEnemy(5, 4);
    gsc.AddEnemy(7, 4);

    // AddEnemy()
    // keypad(stdscr, TRUE); // поддержкf стрелок (не заработало, юзаем wasd пока, потом поправить)

    gsc.DrawGameSpace();
    std::chrono::steady_clock::time_point player_start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point enemy_start_time = std::chrono::steady_clock::now();
    while (true) {
        char ch = getch(); // ch - нажатая клавиша
        char tolower(char ch); // к нижнему регистру
        // Выход по 'L' (можно поставить любую клавишу чтобы останавливать игру в терминале, жать control c каждый раз не оч удобно просто)
        if (ch == 'l' or ch == 'L') {
            break;
        }
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now(); // текущее время
        std::chrono::duration<double> player_timer = now - player_start_time; // время с последнего обновления
        std::chrono::duration<double> enemy_timer = now - enemy_start_time;

        if (player_timer.count() >= time_player) {
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

            if (ch == 'e') {
                gsc.AddBomb(gsc.getPlayerX(), gsc.getPlayerY());
            }
        }

        if (enemy_timer.count() >= 0.1) {
            enemycon.MoveEnemy(0);
            gsc.DrawGameSpace();
            enemy_start_time = std::chrono::steady_clock::now();
        }
    }
    endwin(); // конец для ncurses, иначе после работы в терминале останется мусор
    return 0;
}