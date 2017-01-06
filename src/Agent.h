//
// Created by TriD on 1/2/2017.
//

#ifndef TERRAGEN_AGENT_H
#define TERRAGEN_AGENT_H

class Map;
class AgentManager;

class Agent {
private:
    int tokens;
    int xPos, yPos;

    AgentManager& agentManager;
protected:
    void setPlace();
    void spendToken() { tokens--; }
    void move(int dx, int dy);
    int getX() { return xPos; }
    int getY() { return yPos; }
    int getTokens() { return tokens; }
    AgentManager& getAgentManager() { return agentManager; }
    void setPosition(int x, int y);
public:
    Agent(int xPos, int yPos, int tokens, AgentManager& agentManager);
    Agent(int tokens, AgentManager &agentManager);

    virtual void act(Map& map) = 0;

    bool isFinished() { return tokens == 0; }
};

#endif //TERRAGEN_AGENT_H
