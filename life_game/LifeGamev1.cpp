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

    //useful constants
    const int HEIGHT = 51;
    const int WIDTH = 80;
    const int GRAPH_HEIGHT = HEIGHT * 12 + 24;//24 space used to show fps
    const int GRAPH_WIDTH = WIDTH * 12;
    int DENSITY = 2;
    int SPEED = 30;
    const char FASTER = '=',
               SLOWER = '-',
               DOUBLE = '.',
               HALF = '/';
    LifeGamev1::LifeGamev1() :
        universe(HEIGHT, vector<bool>(WIDTH, false)),
        _universe(HEIGHT, std::vector<bool>(WIDTH, false)),
        myRandom(clock()) {
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
        for (int y = 0; y < HEIGHT; ++y)
            for (int x = 0; x < WIDTH; ++x) {
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
        std::cout << "input the density of the game, eg: 3 means 1/3 is alive, which is black\n";
        std::cin >> DENSITY;
        ShowWindow(GetConsoleWindow(), SW_HIDE);

        for (auto &line : universe) {
            for (auto &u : line) {
                u = myRandom() % DENSITY == 0;
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

                if (isAlive(mod(x + dx, WIDTH), mod(y + dy, HEIGHT))) {
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

        for (int y = 0; y < HEIGHT; ++y)
            for (int x = 0; x < WIDTH; ++x) {
                setfillcolor((*puniverse)[y][x] ? BLACK : WHITE);
                bar(12 * x, 12 * y, 12 * x + 12, 12 * y + 12);
                //              (xl, yt, xr, yb);
            }

        setcolor(EGERGB(0x0, 0xFF, 0xFF));
        setfontbkcolor(EGERGB(0x00, 0x00, 0x00));
        setfont(24, 0, "Consolas");
        std::string fps = "current fps: " + std::to_string(SPEED);
        fps += "        powered by Chen Ji :)";
        outtextxy(0, 12 * HEIGHT, fps.c_str());
    }
}