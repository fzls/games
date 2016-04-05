#define SHOW_CONSOLE
//* ★如果需要显示控制台窗口，请在包含本文件的前面加一行define SHOW_CONSOLE
#include "LifeGamev1.h"
#include <iostream>
#include <ctime>
#include <string>
#include <graphics.h>
using namespace std;
using namespace ege;

namespace LifeGamev1 {
    LifeGamev1::LifeGamev1(unsigned row, unsigned col, unsigned cell_size, unsigned density, int speed) :
        myRandom(clock()),
        universe(row, vector<bool>(col, false)),
        _universe(row, std::vector<bool>(col, false)),
        FONT_SIZE{ 24 },
        ROW{row},
        COL{col},
        GRAPH_HEIGHT{row * cell_size + FONT_SIZE },
        GRAPH_WIDTH{col * cell_size},
        DENSITY{density},
        SPEED{ speed } {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        init(universe);
        _universe = universe;
        puniverse = &universe;
        p_universe = &_universe;
        setinitmode(INIT_ANIMATION);
        initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
        setbkcolor(EGERGB(0xaa, 0xaa, 0xaa));
    }

    LifeGamev1::~LifeGamev1() {
        closegraph();
    }

    void LifeGamev1::play() {
        for (; is_run(); delay_fps(SPEED)) {
            if (kbhit()) {
                changeSetting(getch());
            }

            //原始宇宙为universe,进化后为_universe
            evolve();
            cleardevice();
            render();
        }
    }

    inline void LifeGamev1::evolve() {
        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                evolve(x, y);
            }

        swap(puniverse, p_universe);
    }

    inline void LifeGamev1::evolve(const int x, const int y) {
        int n = neighbour(x, y);

        if (isAlive(x, y)) {
            if (n <= 1 || n >= 4) { die(x, y); } else { reAlive(x, y); }
        } else {
            if (n == 3) { reAlive(x, y); } else { die(x, y); }
        }
    }

    inline void LifeGamev1::init(std::vector<std::vector<bool>> &universe) {
        for (auto &line : universe) {
            for (auto &u : line) {
                u = myRandom() % 100 < DENSITY;
            }
        }
    }

    inline int LifeGamev1::neighbour(const int x, const int y) {
        int result = 0;

        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy) {
                if (dy == 0 && dx == 0) {
                    continue;
                }

                if (isAlive(mod(x + dx, COL), mod(y + dy, ROW))) {
                    ++result;
                }
            }

        return result;
    }

    inline void LifeGamev1::reAlive(const int x, const int y) {
        (*p_universe)[y][x] = true;
    }

    inline int LifeGamev1::mod(int n, const int boundary) {
        return (n + boundary) % boundary;
    }

    inline void LifeGamev1::changeSetting(char cmd) {
        switch (cmd) {
            case FASTER:
                ++SPEED;
                break;

            case SLOWER:
                --SPEED;
                break;

            case DOUBLE:
                SPEED *= 2;
                break;

            case HALF:
                SPEED /= 2;
                break;

            default:
                break;
        }
    }

    inline bool LifeGamev1::isAlive(const int x, const int y) {
        return (*puniverse)[y][x];
    }

    inline void LifeGamev1::die(const int x, const int y) {
        (*p_universe)[y][x] = false;
    }

    inline void LifeGamev1::render() {
        auto WHITE = EGERGB(0xFF, 0xFF, 0xFF);
        auto BLACK = EGERGB(0x0, 0x0, 0x0);

        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                setfillcolor((*puniverse)[y][x] ? BLACK : WHITE);
                bar(12 * x, 12 * y, 12 * x + 12, 12 * y + 12);
                //              (xl, yt, xr, yb);
            }

        setcolor(EGERGB(0x0, 0xFF, 0xFF));
        setfontbkcolor(EGERGB(0x00, 0x00, 0x00));
        setfont(FONT_SIZE, 0, "Consolas");
        std::string fps = "current fps: " + std::to_string(SPEED);
        fps += "        powered by Chen Ji :)";
        outtextxy(0, 12 * ROW, fps.c_str());
    }
}