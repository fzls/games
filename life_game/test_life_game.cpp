/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    test_life_game.cpp
* @version:      v1.0
* @Time:         2016-04-05 16:29:23
* @Description:  the conway's life game
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "LifeGamev1.h"
#include "LifeGamev2.h"
#include "LifeGamev3.h"
using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion

const int INF = 0x7FFFFFFF;

unsigned row = 53,
         col = 80,
         cell_size = 12,
         density = 50,
         game_mode = 1;
int speed = 30,
    step = 4;
vector<unsigned> modes;
const unsigned BLACK_WHITE = 1,
               GREY = 2,
               COLORFUL = 3;
void prompt_if_change_setting() {
    string menu =
        "|----------------------------------------------------|\n"
        "|  Do you want to change the setting?                |\n"
        "|  row, col, cell size and density of init state     |\n"
        "|   0->nope                                          |\n"
        "|   1->row                                           |\n"
        "|   2->col                                           |\n"
        "|   3->cell_size                                     |\n"
        "|   4->density                                       |\n"
        "|   5->init_speed                                    |\n"
        "|   6->die_step                                      |\n"
        "|   7->game mode                                     |\n"
        "|----------------------------------------------------|\n"
        " your choice: ";
    char cmd;

    while(true) {
        system("cls");
        cout << menu;
        cin >> cmd;

        switch (cmd) {
            case '0':
                return;

            case '1':
                cout << "row now is 53, enter your version : "; cin >> row;
                break;

            case '2':
                cout << "col now is 80, enter your version : "; cin >> col;
                break;

            case '3':
                cout << "cell_size now is 12(pixel), enter your version : "; cin >> cell_size;
                break;

            case '4':
                cout << "density now is 50(%), enter your version : "; cin >> density;
                break;

            case '5':
                cout << "speed now is 30 fps, enter your version : "; cin >> speed;
                break;

            case '6':
                cout << "die speed now is 4, enter your version : "; cin >> step;
                break;

            case '7':
                cout << "game mode now is 1(black and white),\n"
                     "the other is 2(grey ver), 3(colorful ver)\n"
                     "enter your version : "; cin >> game_mode;

                if(find(modes.begin(), modes.end(), game_mode) == modes.end()) {
                    cout << "no such game mode\n";
                }

                break;

            default:
                cout << "wrong argument\n";
                break;
        }
    }
}

int main() {
    modes.push_back(BLACK_WHITE); modes.push_back(GREY); modes.push_back(COLORFUL);
    prompt_if_change_setting();

    if (game_mode == BLACK_WHITE) {
        LifeGamev1::LifeGamev1 game(row, col, cell_size, density, speed);
        game.play();
    } else if (game_mode == GREY) {
        LifeGamev2::LifeGamev2 game(row, col, cell_size, density, speed, step);
        game.play();
    } else if (game_mode == COLORFUL) {
        LifeGamev3::LifeGamev3 game(row, col, cell_size, density, speed, step);
        game.play();
    }

    return 0;
}
