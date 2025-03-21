#include <ncurses.h>
#include <cctype>
#include <iostream>
#include <chrono>
#include <thread>
#include "GameSpaceController.h"
#include "PlayerController.h"
#include "Structures.h"
#include "EnemyController.h"
#include "BombController.h"


int main() {
    setlocale(LC_ALL, ""); // для отображения эмодзи
    initscr(); // для ncurses
    start_color(); // Включить поддержку цветов
    
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    auto time_player = 0.09; // время которое отсекается между нажатиями wasd подобрать по ощущениям
    std::vector<Enemy> enemies; // по архитектуре надо будет уточнить, но скорее всего так будет норм
    std::vector<Bomb> bombs;
    std::vector<Explosion> explosions;
    // списки врагов, бомб итд создаются тут, потом закидываем ссылки тому кому они нужны

    GameSpaceController gsc(enemies, bombs, explosions); // ВНИМАНИЕ, это должно быть единственное место где инициализирвоан gsc, повторная инициализация = потеря игрового поля
    BombController bombcon(bombs, gsc, explosions);
    EnemyController enemycon(enemies, gsc);

    PlayerController player(gsc);
    noecho(); // откл отображение вводимых символов и мигающего курсора
    curs_set(0);
    cbreak();
    nodelay(stdscr, TRUE); // нет ожидания введения символов через getch
    enemycon.AddEnemy(5, 4);
    enemycon.AddEnemy(7, 4);
    enemycon.AddEnemy(8, 9);
    enemycon.AddEnemy(1, 2);

    gsc.DrawGameSpace();
    std::chrono::steady_clock::time_point player_start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point enemy_start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point bomb_check_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point fps = std::chrono::steady_clock::now();

    while (true) {
        char ch = getch(); // ch - нажатая клавиша
        char tolower(char ch); // к нижнему регистру
        if (ch == 'e') {
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
            
            if (ch == 'f') { // проверка что можно ставить бомбы
                if (player.GetBombsAllowed() >= bombs.size() + 1) {
                    gsc.AddBomb(gsc.getPlayerX(), gsc.getPlayerY());
                }
            }
        }

        if (enemy_timer.count() >= 0.4) {
            enemycon.MoveEnemies();
            // gsc.DrawGameSpace();
            enemy_start_time = std::chrono::steady_clock::now();
        }
        if (bomb_check_timer.count() >= 0.2) {
            bombcon.CheckBombs();
            bomb_check_time = std::chrono::steady_clock::now();
        }
        if (draw_timer.count() >= 0.001) {
            res = gsc.DrawGameSpace();
        }
        if (res == false) {
            endwin();
            std::cout << "   ####     ##     ##   ##  #######            #####   ##   ##  #######  ######  \n"
            "  ##  ##   ####    ### ###   ##   #           ##   ##  ##   ##   ##   #   ##  ## \n"
            " ##       ##  ##   #######   ## #             ##   ##   ## ##    ## #     ##  ## \n"
            " ##       ##  ##   #######   ####             ##   ##   ## ##    ####     #####  \n"
            " ##  ###  ######   ## # ##   ## #             ##   ##    ###     ## #     ## ##  \n"
            "  ##  ##  ##  ##   ##   ##   ##   #           ##   ##    ###     ##   #   ##  ## \n"
            "   #####  ##  ##   ##   ##  #######            #####      #     #######  #### ## \n";
            endwin();
            return 0;
        }

        if (enemies.size() == 0) { // условие победы - убить всех врагов
            endwin();
            std::cout << " ##  ##    #####   ##   ##           ##   ##   ####    ##   ## \n"
             " ##  ##   ##   ##  ##   ##           ##   ##    ##     ###  ## \n"
             " ##  ##   ##   ##  ##   ##           ##   ##    ##     #### ## \n"
             "  ####    ##   ##  ##   ##           ## # ##    ##     ## #### \n"
             "   ##     ##   ##  ##   ##           #######    ##     ##  ### \n"
             "   ##     ##   ##  ##   ##           ### ###    ##     ##   ## \n"
             "  ####     #####    #####            ##   ##   ####    ##   ## \n";
            endwin();
            return 0;
        }
    }
    endwin(); // конец для ncurses, иначе после работы в терминале останется мусор
    return 0;
}