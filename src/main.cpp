#include <sfml/Graphics.hpp>
#include "Map.h"
#include "MapGenerator.h"


int main() {
    sf::RenderWindow window;
    window.create({512, 512}, "Terrain Test");

    Map map;

    MapGenerator mapgen(map);
    mapgen.generate();

    sf::Texture texture;
    texture.create(512, 512);
    sf::Sprite sprite(texture);

    sf::Uint8* pixelData = new sf::Uint8[512 * 512 * 4];

    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {
            // Filling pixel data with white color for ground and black for water
            pixelData[i * 4 + j * 512 * 4] = map.getItem(i, j) > 0 ? 0 : 0;
            pixelData[i * 4 + j * 512 * 4 + 1] = map.getItem(i, j) > 0 ? 255 : 0;
            pixelData[i * 4 + j * 512 * 4 + 2] = map.getItem(i, j) > 0 ? 0 : 255;
            pixelData[i * 4 + j * 512 * 4 + 3] = 255;
        }
    }
    texture.update(pixelData);

    while (true) {
        window.draw(sprite);
        window.display();
    }

    return 0;
}