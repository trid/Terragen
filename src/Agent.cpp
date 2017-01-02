//
// Created by TriD on 1/2/2017.
//

#include <sfml/Graphics.hpp>

#include "Agent.h"
#include "AgentManager.h"
#include "Map.h"
#include "RandomInt.h"

Agent::Agent(int tokens, AgentManager &agentManager) : tokens(tokens), agentManager(agentManager) {
    RandomInt& random = RandomInt::getInstance();
    xPos = random.nextInt(100, 400);
    yPos = random.nextInt(100, 400);
    setPlace();
    initialize();
}

int Agent::getTokens() const {
    return tokens;
}

void Agent::act(Map &map) {
    scoreAndSet(map);
    randomMove();
    setPlace();
    if (tokens == 0) {
        finished = true;
    }
}

Agent::Agent(int xPos, int yPos, int tokens, AgentManager &agentManager):
xPos(xPos), yPos(yPos),
tokens(tokens), agentManager(agentManager)
{
    setPlace();
    initialize();
}

void Agent::setPlace() {
    if (xPos < 0) {
        xPos = 0;
    }
    if (xPos >= 512) {
        xPos = 511;
    }
    if (yPos < 0) {
        yPos = 0;
    }
    if (yPos >= 512) {
        yPos = 511;
    }
}

void Agent::initialize() {
    if (tokens >= minTokens) {
        agentManager.addAgent(xPos + 1, yPos + 1, tokens / 2);
        agentManager.addAgent(xPos - 1, yPos - 1, tokens / 2);
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

void Agent::scoreAndSet(Map &map) {
    sf::Vector2i maxPos;
    float maxScore = 0;
    float currentScore;

    auto isEligible = [](int xPos, int yPos){
        return !(xPos < 0 || xPos > 511 || yPos < 0 || yPos > 511);
    };

    auto countScore = [&](int xPos, int yPos) -> int{
        if (!isEligible(xPos, yPos)) {
            return 0;
        }
        return scorePoint(xPos, yPos);
    };

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
        map.setItem(maxPos.x, maxPos.y, 1.f);
        tokens--;
    }
}

int Agent::scorePoint(int x, int y) {
    int dr = (xRepulsor - x) * (xRepulsor - x) + (yRepulsor - y) * (yRepulsor - y);
    int da = (xAttractor - x) * (xAttractor - x) + (yAttractor - y) * (yAttractor - y);
    // Closest edge coordinate
    int cex = x < 255 ? 0 : 511;
    int cey = y < 255 ? 0 : 511;

    int de = (cex - x) * (cex - x) + (cey - y) * (cey - y);

    return dr - da + 3 * de;
}

void Agent::randomMove() {
    RandomInt& rand = RandomInt::getInstance();
    xPos += rand.nextInt(-1, 1);
    yPos += rand.nextInt(-1, 1);
}
