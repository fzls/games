#define SHOW_CONSOLE
//* ★如果需要显示控制台窗口，请在包含本文件的前面加一行define SHOW_CONSOLE
#include "LifeGamev2.h"
#include <iostream>
#include <ctime>
#include <string>
#include <graphics.h>
using namespace std;
using namespace ege;

namespace LifeGamev2 {
    LifeGamev2::LifeGamev2(unsigned row, unsigned col, unsigned cell_size, unsigned density, int speed, int step) :
        myRandom(clock()),
        universe(row, vector<Grayscale>(col)),
        _universe(row, std::vector<Grayscale>(col)),
        FONT_SIZE{ 24 },
        ROW{ row },
        COL{ col },
        GRAPH_HEIGHT{ row * cell_size + FONT_SIZE },
        GRAPH_WIDTH{ col * cell_size },
        DENSITY{ density },
        SPEED{ speed },
        STEP{ step } {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        init(universe);
        _universe = universe;
        puniverse = &universe;
        p_universe = &_universe;
        setinitmode(INIT_ANIMATION);
        initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
        setbkcolor(EGERGB(0xaa, 0xaa, 0xaa));
    }

    LifeGamev2::~LifeGamev2() {
        closegraph();
    }

    void LifeGamev2::play() {
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

    inline void LifeGamev2::evolve() {
        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                evolve(x, y);
            }

        swap(puniverse, p_universe);
    }

    inline void LifeGamev2::evolve(const int x, const int y) {
        int n = neighbour(x, y);

        if (isAlive(x, y)) {
            if (n <= 1 || n >= 4) { die(x, y); } else { reAlive(x, y); }
        } else {
            if (n == 3) { reAlive(x, y); } else { die(x, y); }
        }
    }

    inline void LifeGamev2::init(std::vector<std::vector<Grayscale>> &universe) {
        int cnt = 0;

        for (auto &line : universe) {
            for (auto &u : line) {
                u = myRandom() % 128;

                if(cnt++ >= DENSITY) { u = 128 + myRandom() % 128; } //more white

                if (cnt == 100) { cnt = 0; }
            }
        }
    }

    inline int LifeGamev2::neighbour(const int x, const int y) {
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


    inline int LifeGamev2::mod(int n, const int boundary) {
        return (n + boundary) % boundary;
    }

    inline void LifeGamev2::changeSetting(char cmd) {
        switch (cmd) {
            case FASTER:
                ++STEP;
                break;

            case SLOWER:
                --STEP;
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

    inline bool LifeGamev2::isAlive(const int x, const int y) {
        return (*puniverse)[y][x] >= 128;
    }

    inline void LifeGamev2::die(const int x, const int y) {
        (*p_universe)[y][x] -= min((*p_universe)[y][x], STEP);
    }

    inline void LifeGamev2::reAlive(const int x, const int y) {
        (*p_universe)[y][x] += min(255 - (*p_universe)[y][x], STEP);
    }

    inline void LifeGamev2::render() {
        static Grayscale scale;

        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                scale = (*puniverse)[y][x];
                setfillcolor(EGERGB(scale, scale, scale));
                bar(12 * x, 12 * y, 12 * x + 12, 12 * y + 12);
                //              (xl, yt, xr, yb);
            }

        setcolor(EGERGB(0x0, 0xFF, 0xFF));
        setfontbkcolor(EGERGB(0x00, 0x00, 0x00));
        setfont(FONT_SIZE, 0, "Consolas");
        std::string fps = "current fps: " + std::to_string(SPEED);
        fps += "  step: " + std::to_string(STEP);
        fps += "        powered by Chen Ji :)";
        outtextxy(0, 12 * ROW, fps.c_str());
    }
}