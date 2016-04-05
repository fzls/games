#pragma once


#include <vector>
#include <random>

//only two state
namespace LifeGamev1 {
    class LifeGamev1 {
      public:
        LifeGamev1();
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

        static void changeSetting(char cmd);


        std::default_random_engine myRandom;
        std::vector<std::vector<bool>> universe, _universe;
        std::vector<std::vector<bool>> *puniverse, *p_universe;
    };

}
