//
// Created by TriD on 18.03.2017.
//

#ifndef TERRAGEN_HILLSAGENT_H
#define TERRAGEN_HILLSAGENT_H


#include "Agent.h"

class HillsAgent: public Agent {
public:
    HillsAgent(int tokens, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_HILLSAGENT_H
