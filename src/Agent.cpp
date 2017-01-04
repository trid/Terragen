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
}

Agent::Agent(int xPos, int yPos, int tokens, AgentManager &agentManager):
xPos(xPos), yPos(yPos),
tokens(tokens), agentManager(agentManager)
{
    setPlace();
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

void Agent::move(int dx, int dy) {
    xPos += dx;
    yPos += dy;
}

