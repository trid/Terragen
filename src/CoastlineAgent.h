//
// Created by TriD on 05.01.2017.
//

#ifndef TERRAGEN_COASTLINEAGENT_H
#define TERRAGEN_COASTLINEAGENT_H

#include "Agent.h"

class CoastlineAgent: public Agent {
private:
    // Preferred direction
    int xDir, yDir;
    // Attractor and repulsor points
    int xAttractor, yAttractor;
    int xRepulsor, yRepulsor;

    static const int minTokens = 50;

    void initialize();

    void randomMove();
    void scoreAndSet(Map &map);
    int scorePoint(int x, int y);
public:
    CoastlineAgent(int tokens, AgentManager &agentManager);
    CoastlineAgent(int xPos, int yPos, int tokens, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_COASTLINEAGENT_H
