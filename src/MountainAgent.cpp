//
// Created by TriD on 11.03.2017.
//

#include "MountainAgent.h"

#include "Map.h"
#include "RandomInt.h"

float pi = std::acos(-1.0f);
float halfC = pi / 180.0f;

inline float degToRad(float deg) {
    return deg / halfC;
}

MountainAgent::MountainAgent(int tokens, int minWidth, int maxWidth, AgentManager &agentManager) : Agent(tokens, agentManager) {
    RandomInt &randomInt = RandomInt::getInstance();
    angle = randomInt.nextInt(0, 360);

    height = 6;

    width = randomInt.nextInt(minWidth, maxWidth);
    width *= width;

    xPosF = getX();
    yPosF = getY();

    updateDirection();
}

void MountainAgent::act(Map &map) {
    setPoint(xPosF, yPosF, height, map);
    createRange(map);
    updatePosition(map);
    spendToken();
}

void MountainAgent::updateDirection() {
    angle = distributor(engine);

    dx = std::cos(degToRad(angle));
    dy = std::sin(degToRad(angle));
}

void MountainAgent::updatePosition(Map &map) {
    float nxPosF = xPosF + dx;
    float nyPosF = yPosF + dy;

    if (nxPosF > 0 && nxPosF < 512 && nyPosF > 0 && nyPosF < 512) {
        xPosF = nxPosF;
        yPosF = nyPosF;
        setPosition(static_cast<int>(xPosF), static_cast<int>(yPosF));
    }
}

void MountainAgent::createRange(Map &map) {
    float dist = 0;

    float wdx = std::cos(degToRad(angle + 90));
    float wdy = std::sin(degToRad(angle + 90));

    float curDX{0.0f};
    float curDY{0.0f};

    while (dist < width) {
        curDX += wdx;
        curDY += wdy;


        float wXPosP = xPosF + curDX;
        float wYPosP = yPosF + curDY;

        dist = std::fabs((xPosF - wXPosP) * (xPosF - wXPosP) + (yPosF - wYPosP) * (yPosF - wYPosP));
        float percent = 1 - dist / width;

        if (wXPosP >= 0 && wXPosP < 512 && wYPosP >= 0 && wYPosP < 512) {
            setPoint(wXPosP, wYPosP, height * percent, map);
        }

        float wXPosN = xPosF - curDX;
        float wYPosN = yPosF - curDY;
        if (wXPosN >= 0 && wXPosN < 512 && wYPosN >= 0 && wYPosN < 512) {
            setPoint(wXPosN, wYPosN, height * percent, map);
        }
    }
}

void MountainAgent::setPoint(float xPoint, float yPoint, float height, Map &map) {
    if (map.getItemHeight(static_cast<int>(xPoint), static_cast<int>(yPoint)) > 0) {
        Tile& tile = map.getTile(static_cast<int>(xPoint), static_cast<int>(yPoint));

        if (tile.height < height) {
            tile.height = height;
        }
        tile.type = TileType::Plain;
    }
}
