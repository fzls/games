#pragma once


#include <vector>
#include <random>

//only two state
namespace LifeGamev3 {

    const unsigned int R = 0;
    const unsigned int G = 1;
    const unsigned int B = 2;
    class LifeGamev3 {
        typedef unsigned Color;
      public:
        LifeGamev3(unsigned row = 53, unsigned col = 80, unsigned cell_size = 12, unsigned density = 50);
        ~LifeGamev3();
        void play();
      private:
        struct RGB_ {
            std::vector<Color> rgb;

            RGB_(Color r = 0xff, Color g = 0xff, Color b = 0xff): rgb(3) {
                rgb[R] = r;
                rgb[G] = g;
                rgb[B] = b;
            }
        };
        void evolve();
        void render();
        void evolve(const int x, const int y);
        void evolve(const int x, const int y, unsigned color);

        void init(std::vector<std::vector<RGB_>> &universe);

        int neighbour(const int x, const int y, unsigned color);

        bool isAlive(const int x, const int y, unsigned color);

        void die(const int x, const int y, unsigned color);

        void reAlive(const int x, const int y, unsigned color);

        static int mod(int n, const int boundary);

        void changeSetting(char cmd);


        std::default_random_engine myRandom;
        std::vector<std::vector<RGB_>> universe, _universe;
        std::vector<std::vector<RGB_>> *puniverse, *p_universe;


        //useful constants

        const unsigned int FONT_SIZE;
        const unsigned int ROW;
        const unsigned int COL;
        const unsigned int GRAPH_HEIGHT;//24 space used to show fps
        const unsigned int GRAPH_WIDTH;
        const unsigned int DENSITY;
        int SPEED;
        enum Setting {
            FASTER = '=',
            SLOWER = '-',
            DOUBLE = '.',
            HALF = '/'
        };
    };

}
