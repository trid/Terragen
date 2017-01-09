//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_MAP_H
#define TERRAGEN_MAP_H

#include <vector>
#include "Tile.h"

class Map {
private:
    std::vector<Tile> data;

    static const int width = 512;
    static const int height = 512;
public:
    Map();

    void setItemHeight(int x, int y, float h) { data[x + y * width].height = h; }
    float getItemHeight(int x, int y) { return data[x + y * width].height; }

    Tile& getTile(int x, int y) { return data[x + y * height];}
};


#endif //TERRAGEN_MAP_H
