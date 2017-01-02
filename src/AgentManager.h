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
    void addAgent(int tokens);
    void addAgent(int xPos, int yPos, int tokens);

    void run(Map& map);
};


#endif //TERRAGEN_AGENTMANAGER_H
