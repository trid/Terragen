//
// Created by TriD on 07.01.2017.
//

#ifndef TERRAGEN_TILE_H
#define TERRAGEN_TILE_H

enum class TileType {
    Plain,
    Beach,
    River,
    Mountain
};

struct Tile {
    Tile(){}

    float height{-1};
    TileType type{TileType::Plain};
    bool passed;
};


#endif //TERRAGEN_TILE_H
