//
// Created by TriD on 1/6/2017.
//

#include "Map.h"
#include "SmoothingAgent.h"
#include "RandomInt.h"

SmoothingAgent::SmoothingAgent(int initialX, int initialY, int tokens, int steps, AgentManager &agentManager)
        : Agent(initialX, initialY, tokens, agentManager),
          steps(steps), initialSteps(steps) {
    this->initialX = initialX;
    this->initialY = initialY;
}

void SmoothingAgent::act(Map &map) {
    if (steps == 0) {
        setPosition(initialX, initialY);
        spendToken();
        steps = initialSteps;
    }
    smooth(map);
    randomMove();
    setPlace();
    steps--;
}

void SmoothingAgent::randomMove() {
    RandomInt& rand = RandomInt::getInstance();
    move(rand.nextInt(-1, 1), rand.nextInt(-1, 1));
    setPlace();
}

void SmoothingAgent::smooth(Map &map) {
    float sum = 0;
    int cnt = 0;

    auto addVal = [&](int x, int y){
        if (x < 0 || x > 512 || y < 0 || y > 512) {
            return;
        }
        cnt++;
        sum += map.getItem(x, y);
    };

    int xPos = getX();
    int yPos = getY();

    addVal(xPos, yPos - 1);
    addVal(xPos, yPos - 2);
    addVal(xPos + 1, yPos);
    addVal(xPos + 2, yPos);
    addVal(xPos, yPos + 1);
    addVal(xPos, yPos + 2);
    addVal(xPos - 1, yPos);
    addVal(xPos - 2, yPos);
    addVal(xPos + 1, yPos - 1);
    addVal(xPos + 1, yPos + 1);
    addVal(xPos - 1, yPos + 1);
    addVal(xPos - 1, yPos - 1);

    map.setItem(xPos, yPos, sum / cnt);
}
