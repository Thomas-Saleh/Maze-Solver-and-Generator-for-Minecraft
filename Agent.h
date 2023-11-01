#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    Agent(mcpp::Coordinate startLoc);
    ~Agent();
    

   
    void initializePlayerBlock();
    void guideToExit();

    mcpp::Coordinate getNextLocation(const mcpp::Coordinate& currentLocation, AgentOrientation orientation);
    AgentOrientation getNewOrientation(const mcpp::Coordinate& currentLocation, const mcpp::Coordinate& nextLocation);
    AgentOrientation turnLeft(AgentOrientation orientation);
    AgentOrientation turnBack(AgentOrientation orientation);
    AgentOrientation turnRight(AgentOrientation orientation);
    bool CheckIfExit(mcpp::MinecraftConnection& mc, mcpp::Coordinate currentLocation, AgentOrientation currentOrientation);

    



private:
    /* data */
    AgentOrientation currentOrientation; 

    mcpp::MinecraftConnection mc;

};



#endif //ASSIGN3_AGENT_H