//
// Created by TriD on 05.01.2017.
//

#include <limits>
#include <SFML/System.hpp>
#include "AgentManager.h"
#include "CoastlineAgent.h"
#include "Map.h"
#include "RandomInt.h"

CoastlineAgent::CoastlineAgent(int tokens, AgentManager &agentManager) : Agent(tokens, agentManager) {
    initialize();
}

CoastlineAgent::CoastlineAgent(int xPos, int yPos, int tokens, AgentManager &agentManager) : Agent(xPos, yPos, tokens,
                                                                                                   agentManager) {
    initialize();
}

void CoastlineAgent::act(Map &map) {
    scoreAndSet(map);
    randomMove();
    setPlace();
}

void CoastlineAgent::randomMove() {
    RandomInt& rand = RandomInt::getInstance();
    move(rand.nextInt(-1, 1), rand.nextInt(-1, 1));
    setPlace();
}

void CoastlineAgent::scoreAndSet(Map &map) {
    sf::Vector2i maxPos;
    int maxScore = std::numeric_limits<int>::min();
    int currentScore;

    auto isEligible = [](int xPos, int yPos){
        return !(xPos < 0 || xPos > 511 || yPos < 0 || yPos > 511);
    };

    auto countScore = [&](int xPos, int yPos) -> int{
        if (!isEligible(xPos, yPos)) {
            return std::numeric_limits<int>::min();
        }
        return scorePoint(xPos, yPos);
    };

    int xPos = getX();
    int yPos = getY();

    if ((currentScore = countScore(xPos, yPos - 1)) > maxScore) {
        maxPos = {xPos, yPos - 1};
        maxScore = currentScore;
    }
    if ((currentScore = countScore(xPos + 1, yPos)) > maxScore) {
        maxPos = {xPos + 1, yPos};
        maxScore = currentScore;
    }
    if ((currentScore = scorePoint(xPos, yPos + 1)) > maxScore) {
        maxPos = {xPos, yPos + 1};
        maxScore = currentScore;
    }
    if (scorePoint(xPos - 1, yPos) > maxScore) {
        maxPos = {xPos - 1, yPos};
    }

    if (map.getItem(maxPos.x, maxPos.y) < 0) {
        map.setItem(maxPos.x, maxPos.y, RandomInt::getInstance().nextInt(1, 5));
        spendToken();
    }
}

int CoastlineAgent::scorePoint(int x, int y) {
    int dr = (xRepulsor - x) * (xRepulsor - x) + (yRepulsor - y) * (yRepulsor - y);
    int da = (xAttractor - x) * (xAttractor - x) + (yAttractor - y) * (yAttractor - y);
    // Closest edge coordinate
    int cex = x < 255 ? 0 : 511;
    int cey = y < 255 ? 0 : 511;

    int de = (cex - x) * (cex - x) + (cey - y) * (cey - y);

    return dr - da + 3 * de;
}

void CoastlineAgent::initialize() {
    int tokens = getTokens();

    if (tokens >= minTokens) {
        getAgentManager().addCoastlineAgent(getX() + 1, getY() + 1, tokens / 2);
        getAgentManager().addCoastlineAgent(getX() - 1, getY() - 1, tokens / 2);
    }

    RandomInt& random = RandomInt::getInstance();

    while (xDir == 0 || yDir == 0) {
        xDir = random.nextInt(-1, 1);
        yDir = random.nextInt(-1, 1);
    }

    xAttractor = random.nextInt(0, 511);
    yAttractor = random.nextInt(0, 511);

    xRepulsor = random.nextInt(0, 511);
    yRepulsor = random.nextInt(0, 511);
}
