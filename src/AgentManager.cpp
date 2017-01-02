//
// Created by TriD on 1/2/2017.
//

#include "AgentManager.h"

#include "Agent.h"

void AgentManager::addAgent(int tokens) {
    agents.emplace_back(new Agent(tokens, *this));

}

void AgentManager::addAgent(int xPos, int yPos, int tokens) {
    agents.emplace_back(new Agent(xPos, yPos, tokens, *this));
}

void AgentManager::run(Map &map) {
    while (!agents.empty()) {
        for (auto& agent: agents) {
            agent->act(map);
        }
        agents.remove_if([](AgentPtr& agentPtr) { return agentPtr->isFinished(); });
    }
}
