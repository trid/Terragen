//
// Created by TriD on 07.01.2017.
//

#ifndef TERRAGEN_BEACHAGENT_H
#define TERRAGEN_BEACHAGENT_H

#include <queue>
#include <sfml/System.hpp>
#include "Agent.h"

class Map;

class BeachAgent: public Agent {
private:
    static std::queue<sf::Vector2i> beachPoints;

    int maxHeight = 2;
    int maxDistSq;
    int currMaxDist;
    bool isWorking{false};
    int steps;
    int maxSteps;
    int initialX, initialY;

    void randomMove(Map &map);
public:
    static void updateBeachPoints(Map& map);

    BeachAgent(int maxDist, int maxSteps, int maxHeight, int tokens, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_BEACHAGENT_H
