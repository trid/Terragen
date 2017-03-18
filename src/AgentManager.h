//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_AGENTMANAGER_H
#define TERRAGEN_AGENTMANAGER_H

#include <memory>
#include <queue>
#include <list>

class Agent;
class Map;

using AgentPtr = std::unique_ptr<Agent>;

class AgentManager {
private:
    std::list<AgentPtr> agents;
public:
    void addCoastlineAgent(int tokens);
    void addCoastlineAgent(int xPos, int yPos, int tokens);

    void addSmoothingAgents(int count, int initialSteps, int tokens);

    void addBeachAgents(int count, int maxHeight, int maxSteps, int maxDist, int tokens);

    void addMountainAgents(int count, int minWidth, int maxWidth, int tokens);

    void addHillsAgents(int count, int minWidth, int maxWidth, int tokens);

    void run(Map& map);
};


#endif //TERRAGEN_AGENTMANAGER_H
