//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_MAPGENERATOR_H
#define TERRAGEN_MAPGENERATOR_H


#include "Map.h"

class MapGenerator {
private:
    Map& map;
public:
    MapGenerator(Map &map);

    void generate();
};


#endif //TERRAGEN_MAPGENERATOR_H
