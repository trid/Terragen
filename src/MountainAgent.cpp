//
// Created by TriD on 11.03.2017.
//

#include "MountainAgent.h"

#include "Map.h"
#include "RandomInt.h"

namespace {
    float pi = std::acos(-1.0f);
    float halfC = pi / 180.0f;

    inline float degToRad(float deg) {
        return deg / halfC;
    }
}

MountainAgent::MountainAgent(int tokens, int minWidth, int maxWidth, AgentManager &agentManager) : Agent(tokens, agentManager),
minWidth(minWidth), maxWidth(maxWidth)
{
    RandomInt &randomInt = RandomInt::getInstance();

    angle = randomInt.nextInt(0, 360);

    height = randomInt.nextInt(4, 6);

    width = randomInt.nextInt(minWidth, maxWidth);
    width *= width;

    xPosF = getX();
    yPosF = getY();

    stepsToRotate = randomInt.nextInt(60, 100);

    updateDirection();
}

void MountainAgent::act(Map &map) {
    setPoint(xPosF, yPosF, height, map);
    createRange(map);
    updatePosition(map);
    spendToken();

    if (steps == 0) {
        makeCircle(map);
    }

    steps++;

    if (steps >= stepsToRotate) {
        steps = 0;
        resetWidthAndDirection();
    }

    if (isFinished()) {
        makeCircle(map);
    }
}

void MountainAgent::updateDirection() {
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
            setPoint(wXPosP, wYPosP - 1, height * percent, map);
            setPoint(wXPosP + 1, wYPosP, height * percent, map);
            setPoint(wXPosP, wYPosP + 1, height * percent, map);
            setPoint(wXPosP - 1, wYPosP, height * percent, map);
        }

        float wXPosN = xPosF - curDX;
        float wYPosN = yPosF - curDY;
        if (wXPosN >= 0 && wXPosN < 512 && wYPosN >= 0 && wYPosN < 512) {
            setPoint(wXPosN, wYPosN, height * percent, map);
            setPoint(wXPosN, wYPosN - 1, height * percent, map);
            setPoint(wXPosN + 1, wYPosN, height * percent, map);
            setPoint(wXPosN, wYPosN + 1, height * percent, map);
            setPoint(wXPosN - 1, wYPosN, height * percent, map);
        }
    }
}

void MountainAgent::setPoint(float xPoint, float yPoint, float height, Map &map) {
    if (xPoint < 0 || xPoint > 511 || yPoint < 0 || yPoint > 511) {
        return;
    }

    if (map.getItemHeight(static_cast<int>(xPoint), static_cast<int>(yPoint)) > 0) {
        Tile& tile = map.getTile(static_cast<int>(xPoint), static_cast<int>(yPoint));

        if (tile.height < height) {
            tile.height = height;
        }
        tile.type = TileType::Mountain;
    }
}

void MountainAgent::makeCircle(Map &map) {
    float x = std::sqrt(width);
    float y = 0;
    float err = -x;

    while (x >= y) {
        makeLine(xPosF - y, xPosF + y, yPosF + x, map);
        makeLine(xPosF - x, xPosF + x, yPosF + y, map);
        makeLine(xPosF - x, xPosF + x, yPosF - y, map);
        makeLine(xPosF - y, xPosF + y, yPosF - x, map);

        if (err <= 0) {
            ++y;
            err += 2 * y + 1;
        }
        else {
            --x;
            err -= 2 * x + 1;
        }
    }
}

void MountainAgent::makeLine(float startX, float endX, float y, Map &map) {
    startX = startX < 0 ? 0 : startX;
    endX = endX > 511 ? 511 : endX;

    y = y < 0 ? 0 : y;
    y = y > 511 ? 511 : y;

    for (float i = startX; i <= endX; i += 1.0) {
        float dist = std::fabs((xPosF - i) * (xPosF - i) + (yPosF - y) * (yPosF - y));
        float height = (1 - dist/width) * this->height;

        setPoint(i, y, height, map);
    }
}

void MountainAgent::resetWidthAndDirection() {
    RandomInt& randomInt = RandomInt::getInstance();

    angle += randomInt.nextInt(-45, 45);
    updateDirection();

    width = randomInt.nextInt(minWidth, maxWidth);
    width *= width;
}

void MountainAgent::smoothe(float xPos, float yPos, Map &map) {
    if (xPos < 0 || xPos > 511 || yPos < 0 || yPos > 511 || map.getItemHeight(xPos, yPos) < 0) {
        return;
    }

    int cnt{0};
    float sumHeight{0};

    auto addToSumm = [&](float nxPos, float nyPos) {
        if (nxPos < 0 || nxPos > 511) {
            return;
        }
        if (nyPos < 0 || nyPos > 511) {
            return;
        }
        if (map.getItemHeight(nxPos, nyPos) <= 0) {
            return;
        }
        cnt++;
        sumHeight += map.getItemHeight(nxPos, nyPos);
    };

    addToSumm(xPos, yPos - 1);
    addToSumm(xPos + 1, yPos);
    addToSumm(xPos, yPos - 1);
    addToSumm(xPos - 1, yPos);

    if (cnt != 0) {
        map.setItemHeight(xPos, yPos, sumHeight / cnt);
    }
}
