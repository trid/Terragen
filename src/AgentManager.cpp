//
// Created by TriD on 1/2/2017.
//

#include "AgentManager.h"

#include "Agent.h"
#include "CoastlineAgent.h"
#include "SmoothingAgent.h"
#include "BeachAgent.h"

void AgentManager::addCoastlineAgent(int tokens) {
    agents.emplace_back(new CoastlineAgent(tokens, *this));

}

void AgentManager::addCoastlineAgent(int xPos, int yPos, int tokens) {
    agents.emplace_back(new CoastlineAgent(xPos, yPos, tokens, *this));
}

void AgentManager::run(Map &map) {
    while (!agents.empty()) {
        for (auto& agent: agents) {
            agent->act(map);
        }
        agents.remove_if([](AgentPtr& agentPtr) { return agentPtr->isFinished(); });
    }
}

void AgentManager::addSmoothingAgents(int count, int initialSteps, int tokens) {
    int xNum = count / 2;
    int yNum = xNum;

    int stepX = 512 / xNum;
    int stepY = stepX;

    for (int x = 0; x < xNum; x++) {
        for (int y = 0; y < yNum; y++) {
            agents.emplace_back(new SmoothingAgent(x * stepX, y * stepY, tokens, initialSteps, *this));
        }
    }
}

void AgentManager::addBeachAgents(int count, int maxHeight, int maxSteps, int maxDist, int tokens) {
    for (int i = 0; i < count; i++) {
        agents.emplace_back(new BeachAgent(maxDist, maxSteps, maxHeight, tokens, *this));
    }
}
