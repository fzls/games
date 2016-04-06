#pragma once


#include <vector>
#include <random>

//only two state
namespace LifeGamev1 {
    class LifeGamev1 {
      public:
        LifeGamev1(unsigned row = 53, unsigned col = 80, unsigned cell_size = 12, unsigned density = 50, int speed = 30);
        ~LifeGamev1();
        void play();
      private:
        void evolve();
        void render();
        void evolve(const int x, const int y);

        void init(std::vector<std::vector<bool>> &universe);

        int neighbour(const int x, const int y);

        bool isAlive(const int x, const int y) ;

        void die(const int x, const int y) ;

        void reAlive(const int x, const int y);

        static int mod(int n, const int boundary);

        void changeSetting(char cmd);


        std::default_random_engine myRandom;
        std::vector<std::vector<bool>> universe, _universe;
        std::vector<std::vector<bool>> *puniverse, *p_universe;


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
