//
// Created by TriD on 1/6/2017.
//

#ifndef TERRAGEN_SMOOTHINGAGENT_H
#define TERRAGEN_SMOOTHINGAGENT_H


#include "Agent.h"

class SmoothingAgent: public Agent {
private:
    int steps;
    int initialSteps;

    int initialX, initialY;

    void randomMove();
    void smooth(Map &map);
public:
    SmoothingAgent(int initialX, int initialY, int tokens, int steps, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_SMOOTHINGAGENT_H
