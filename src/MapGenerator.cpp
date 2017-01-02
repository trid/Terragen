//
// Created by TriD on 1/2/2017.
//

#include "MapGenerator.h"
#include "AgentManager.h"
#include "Agent.h"

MapGenerator::MapGenerator(Map &map) : map(map) {}

void MapGenerator::generate() {
    AgentManager agentManager;

    for (int i = 0; i < 80; i++) {
        agentManager.addAgent(5000);
        agentManager.run(map);
    }
}
