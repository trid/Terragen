//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_MAP_H
#define TERRAGEN_MAP_H

#include <vector>

class Map {
private:
    std::vector<float> data;

    static const int width = 512;
    static const int height = 512;
public:
    Map();

    void setItem(int x, int y, float h) { data[x + y * width] = h; }
    float getItem(int x, int y) { return data[x + y * width]; }
};


#endif //TERRAGEN_MAP_H
