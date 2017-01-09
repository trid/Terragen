#include <sfml/Graphics.hpp>
#include "Map.h"
#include "MapGenerator.h"

void setPixelColor(int x, int y, sf::Uint8* pixelData, Map& map) {
    if (map.getTile(x, y).type == TileType::Beach) {
        pixelData[x * 4 + y * 512 * 4] = 233;
        pixelData[x * 4 + y * 512 * 4 + 1] = 244;
        pixelData[x * 4 + y * 512 * 4 + 2] = 66;
        pixelData[x * 4 + y * 512 * 4 + 3] = 255;
        return;
    }
    if (map.getItemHeight(x, y) < 0) {
        pixelData[x * 4 + y * 512 * 4] = 0;
        pixelData[x * 4 + y * 512 * 4 + 1] = 0;
        pixelData[x * 4 + y * 512 * 4 + 2] = 255;
        pixelData[x * 4 + y * 512 * 4 + 3] = 255;
    }
    else {
        // Filling pixel data with white color for ground and black for water
        float h = map.getItemHeight(x, y);
        pixelData[x * 4 + y * 512 * 4] = static_cast<sf::Uint8>((h / 6) * 255);
        pixelData[x * 4 + y * 512 * 4 + 1] = 255;
        pixelData[x * 4 + y * 512 * 4 + 2] = static_cast<sf::Uint8>((h / 6) * 255);
        pixelData[x * 4 + y * 512 * 4 + 3] = 255;
    }
}

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
            setPixelColor(i, j, pixelData, map);
        }
    }
    texture.update(pixelData);

    while (true) {
        window.draw(sprite);
        window.display();
    }

    return 0;
}