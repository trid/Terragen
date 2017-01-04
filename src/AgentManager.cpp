//
// Created by TriD on 1/2/2017.
//

#include "AgentManager.h"

#include "Agent.h"
#include "CoastlineAgent.h"

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
