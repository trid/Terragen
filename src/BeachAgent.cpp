//
// Created by TriD on 07.01.2017.
//

#include "BeachAgent.h"

#include "Map.h"
#include "RandomInt.h"

std::queue<sf::Vector2i> BeachAgent::beachPoints{};

BeachAgent::BeachAgent(int maxDist, int maxSteps, int maxHeight, int tokens, AgentManager &agentManager) :
        Agent(tokens, agentManager), maxSteps(maxSteps), maxDistSq(maxDist * maxDist), maxHeight(maxHeight){}

void BeachAgent::updateBeachPoints(Map &map) {
    std::queue<sf::Vector2i> searchQueue;
    searchQueue.push({0, 0});

    auto isOnMap = [](int x, int y) {
        return !(x < 0 || x >= 512 || y < 0 || y >= 512);
    };

    auto addItem = [&](int x, int y) {
        if (!isOnMap(x, y)) {
            return;
        }
        if (!map.getTile(x, y).passed) {
            searchQueue.push({x, y});
        }
    };

    auto checkBeach = [&](int x, int y) {
        if (map.getItemHeight(x, y) < 0) {
            return false;
        }
        if (isOnMap(x, y - 1) && map.getItemHeight(x, y - 1) < 0) return true;
        if (isOnMap(x + 1, y) && map.getItemHeight(x + 1, y) < 0) return true;
        if (isOnMap(x, y + 1) && map.getItemHeight(x, y + 1) < 0) return true;
        if (isOnMap(x - 1, y) && map.getItemHeight(x - 1, y) < 0) return true;
        return false;
    };

    while (!searchQueue.empty()) {
        auto item = searchQueue.front();
        searchQueue.pop();
        Tile& tile = map.getTile(item.x, item.y);

        if (!tile.passed) {
            tile.passed = true;
            addItem(item.x, item.y - 1);
            addItem(item.x + 1, item.y);
            addItem(item.x, item.y + 1);
            addItem(item.x - 1, item.y);

            if (checkBeach(item.x, item.y)) {
                beachPoints.push(item);
            }
        }
    }
}

void BeachAgent::act(Map &map) {
    if (beachPoints.empty()) {
        setFinished();
        return;
    }

    if (!isWorking) {
        sf::Vector2i pos = beachPoints.front();
        beachPoints.pop();
        if (map.getItemHeight(pos.x, pos.y) < maxHeight) {
            isWorking = true;
            setPosition(pos.x, pos.y);
            initialX = pos.x;
            initialY = pos.y;
            map.getTile(pos.x, pos.y).type = TileType::Beach;
            steps = maxSteps;
            currMaxDist = RandomInt::getInstance().nextInt(1, maxDistSq);
        }
        return;
    }

    if (steps > 0) {
        randomMove(map);
        map.getTile(getX(), getY()).type = TileType::Beach;
    }
    else {
        spendToken();
        isWorking = false;
    }
}

void BeachAgent::randomMove(Map &map) {
    steps--;
    RandomInt& rand = RandomInt::getInstance();
    int x = getX() + rand.nextInt(-1, 1);
    int y = getY() + rand.nextInt(-1, 1);

    if (x < 0 || x > 511 || y < 0 || y > 511) {
        return;
    }

    if (map.getItemHeight(x, y) < 0) {
        return;
    }

    if ((initialX - x) * (initialX - x) + (initialY - y) * (initialY - y) > currMaxDist) {
        return;
    }

    move(rand.nextInt(-1, 1), rand.nextInt(-1, 1));
    setPlace();
}
