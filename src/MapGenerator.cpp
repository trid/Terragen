//
// Created by TriD on 1/2/2017.
//

#include "MapGenerator.h"
#include "AgentManager.h"
#include "Agent.h"
#include "BeachAgent.h"

MapGenerator::MapGenerator(Map &map) : map(map) {}

void MapGenerator::generate() {
    AgentManager agentManager;

    for (int i = 0; i < 5; i++) {
        agentManager.addCoastlineAgent(3000);
        agentManager.run(map);
    }

    agentManager.addSmoothingAgents(50, 50, 70);
    agentManager.run(map);

    BeachAgent::updateBeachPoints(map);

    agentManager.addBeachAgents(128, 2, 32, 4, 60);
    agentManager.run(map);

    agentManager.addMountainAgents(3, 25, 50, 600);
    agentManager.run(map);
}
