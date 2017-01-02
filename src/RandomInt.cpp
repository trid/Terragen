//
// Created by TriD on 1/2/2017.
//

#include "RandomInt.h"

RandomInt::RandomInt() {

}

RandomInt &RandomInt::getInstance() {
    static RandomInt randomInt;
    return randomInt;
}

int RandomInt::nextInt(int min, int max) {
    std::uniform_int_distribution<int> distr(min, max);
    return distr(engine);
}

