//
// Created by TriD on 18.03.2017.
//

#ifndef TERRAGEN_HILLSAGENT_H
#define TERRAGEN_HILLSAGENT_H

#include "MountainAgent.h"

class HillsAgent: public Agent {
private:
    float xPosF;
    float yPosF;

    float dx;
    float dy;

    float angle;

    float height;

    float width;

    int minWidth;
    int maxWidth;

    bool firstStep{true};
    int steps{0};
    int stepsToRotate;

    void updateDirection();
    void updatePosition(Map &map);
    void createRange(Map &map);
    void setPoint(float xPoint, float yPoint, float height, Map &map);
    void makeCircle(Map &map);
    void makeLine(float startX, float endX, float y, Map &map);
    void resetWidthAndDirection();
public:
    HillsAgent(int tokens, int minWidth, int maxWidth, AgentManager &agentManager);

    void act(Map &map) override;
};


#endif //TERRAGEN_HILLSAGENT_H
