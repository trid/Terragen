//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_RANDOMINT_H
#define TERRAGEN_RANDOMINT_H

#include <random>

class RandomInt {
private:
    RandomInt();

    std::default_random_engine engine;
public:
    static RandomInt& getInstance();

    int nextInt(int min, int max);
};


#endif //TERRAGEN_RANDOMINT_H
