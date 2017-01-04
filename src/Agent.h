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
    // Preferred direction
    int xDir, yDir;
    int xAttractor, yAttractor;
    int xRepulsor, yRepulsor;
    AgentManager& agentManager;

    bool finished{false};

    static const int minTokens = 50;

    void setPlace();
    void initialize();
    void randomMove();
public:
    Agent(int xPos, int yPos, int tokens, AgentManager& agentManager);
    Agent(int tokens, AgentManager &agentManager);

    int getTokens() const;

    void act(Map& map);

    bool isFinished() { return finished; }

    void scoreAndSet(Map &map);

    int scorePoint(int x, int y);
};

#endif //TERRAGEN_AGENT_H
