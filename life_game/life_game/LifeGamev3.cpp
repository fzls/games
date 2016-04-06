#define SHOW_CONSOLE
//* ★如果需要显示控制台窗口，请在包含本文件的前面加一行define SHOW_CONSOLE
#include "LifeGamev3.h"
#include <iostream>
#include <ctime>
#include <string>
#include <graphics.h>
using namespace std;
using namespace ege;

namespace LifeGamev3 {
    LifeGamev3::LifeGamev3(unsigned row, unsigned col, unsigned cell_size, unsigned density, int speed, int step) :
        myRandom(clock()),
        universe(row, vector<RGB_>(col)),
        _universe(row, std::vector<RGB_>(col)),
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

    LifeGamev3::~LifeGamev3() {
        closegraph();
    }

    void LifeGamev3::play() {
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

    inline void LifeGamev3::evolve() {
        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                evolve(x, y);
            }

        swap(puniverse, p_universe);
    }

    inline void LifeGamev3::evolve(const int x, const int y) {
        evolve(x, y, R);
        evolve(x, y, G);
        evolve(x, y, B);
    }

    inline void LifeGamev3::evolve(const int x, const int y, unsigned color) {
        int n = neighbour(x, y, color);

        if (isAlive(x, y, color)) {
            if (n <= 1 || n >= 4) { die(x, y, color); } else { reAlive(x, y, color); }
        } else {
            if (n == 3) { reAlive(x, y, color); } else { die(x, y, color); }
        }
    }

    inline void LifeGamev3::init(std::vector<std::vector<RGB_>> &universe) {
        Color r, g, b;

        for (auto &line : universe) {
            for (auto &u : line) {
                r = myRandom() % 128;//default dead
                g = myRandom() % 128;
                b = myRandom() % 128;

                if (myRandom() % 100 < DENSITY) {//denisty % is alive
                    r += 128;
                    g += 128;
                    b += 128;
                }

                u = std::move(RGB_(r, g, b));
            }
        }
    }

    inline int LifeGamev3::neighbour(const int x, const int y, unsigned color) {
        int result = 0;

        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy) {
                if (dy == 0 && dx == 0) {
                    continue;
                }

                if (isAlive(mod(x + dx, COL), mod(y + dy, ROW), color)) {
                    ++result;
                }
            }

        return result;
    }


    inline int LifeGamev3::mod(int n, const int boundary) {
        return (n + boundary) % boundary;
    }

    inline void LifeGamev3::changeSetting(char cmd) {
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

    inline bool LifeGamev3::isAlive(const int x, const int y, unsigned color) {
        return (*puniverse)[y][x].rgb[color] >= 128;
    }

    inline void LifeGamev3::die(const int x, const int y, unsigned color) {
        (*p_universe)[y][x].rgb[color] -= min((*p_universe)[y][x].rgb[color], STEP);
    }

    inline void LifeGamev3::reAlive(const int x, const int y, unsigned color) {
        (*p_universe)[y][x].rgb[color] += min(255 - (*p_universe)[y][x].rgb[color], STEP);
    }

    inline void LifeGamev3::render() {
        static Color r, g, b;

        for (unsigned y = 0; y < ROW; ++y)
            for (unsigned x = 0; x < COL; ++x) {
                r = (*puniverse)[y][x].rgb[R];
                g = (*puniverse)[y][x].rgb[G];
                b = (*puniverse)[y][x].rgb[B];
                setfillcolor(EGERGB(r, g, b));
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