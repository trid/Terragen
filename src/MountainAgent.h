//
// Created by TriD on 11.03.2017.
//

#ifndef TERRAGEN_MOUNTAINAGENT_H
#define TERRAGEN_MOUNTAINAGENT_H


#include <random>
#include "Agent.h"

class MountainAgent: public Agent {
private:
    float xPosF;
    float yPosF;

    float dx;
    float dy;

    float angle;

    float height;

    float width;

    std::uniform_int_distribution<int> distributor{0, 360};
    std::default_random_engine engine;

    void updateDirection();
    void updatePosition(Map &map);
    void createRange(Map &map);
    void setPoint(float xPoint, float yPoint, float height, Map &map);
public:
    MountainAgent(int tokens, int minWidth, int maxWidth, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_MOUNTAINAGENT_H
