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
    std::vector<Enemy> enemies; // по архитектуре надо будет уточнить, но скорее всего так будет норм
    std::vector<Bomb> bombs;
    std::vector<Explosion> explosions;
    // списки врагов, бомб итд создаются тут, потом закидываем ссылки тому кому они нужны
    // EnemyController enemycon(enemies, gsc);

    GameSpaceController gsc(enemies, bombs, explosions); // ВНИМАНИЕ, это должно быть единственное место где инициализирвоан gsc, повторная инициализация = потеря игрового поля
    BombController bombcon(bombs, gsc, explosions);
    EnemyController enemycon(enemies, gsc);

    PlayerController player(gsc);
    noecho(); // откл отображение вводимых символов и мигающего курсора
    setlocale(LC_ALL, "");
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    gsc.AddEnemy(5, 4);
    gsc.AddEnemy(7, 4);
    // player.MovePlayer(10, 5);

    // AddEnemy()
    // keypad(stdscr, TRUE); // поддержкf стрелок (не заработало, юзаем wasd пока, потом поправить)

    gsc.DrawGameSpace();
    std::chrono::steady_clock::time_point player_start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point enemy_start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point bomb_check_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point fps = std::chrono::steady_clock::now();
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
        std::chrono::duration<double> bomb_check_timer = now - bomb_check_time;
        std::chrono::duration<double> draw_timer = now - fps;
        bool res = true;
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
                // Bomb newBomb = {3, 5}; что это такое?? какой еще newBomb, зачем
            }
        }

        if (enemy_timer.count() >= 0.5) {
            enemycon.MoveEnemy(0);
            // gsc.DrawGameSpace();
            enemy_start_time = std::chrono::steady_clock::now();
        }
        if (bomb_check_timer.count() >= 0.5) {
            bombcon.CheckBombs();
            bomb_check_time = std::chrono::steady_clock::now();
        }

        if (draw_timer.count() >= 0.4) {
            res = gsc.DrawGameSpace();
        }
        if (res == false) {
            endwin();
            std::cout << " ##  ##    #####   ##   ##           ####      #####    #####   ######  \n"
            " ##  ##   ##   ##  ##   ##            ##      ##   ##  ##   ##  # ## #  \n"
            " ##  ##   ##   ##  ##   ##            ##      ##   ##  #          ##    \n"
            "  ####    ##   ##  ##   ##            ##      ##   ##   #####     ##    \n"
            "   ##     ##   ##  ##   ##            ##   #  ##   ##       ##    ##    \n"
            "   ##     ##   ##  ##   ##            ##  ##  ##   ##  ##   ##    ##    \n"
            "  ####     #####    #####            #######   #####    #####    ####   \n";
            endwin();
            return 0;
        }
    }
    endwin(); // конец для ncurses, иначе после работы в терминале останется мусор
    return 0;
}