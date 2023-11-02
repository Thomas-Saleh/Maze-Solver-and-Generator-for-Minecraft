#include "Agent.h"
#include <thread>
#include <chrono>
#include <string>

Agent::Agent(mcpp::Coordinate startLoc)
{
}

Agent::~Agent()
{
}

// Initialize the player's block and orientation.
void Agent::initializePlayerBlock()
{
    mcpp::MinecraftConnection mc;
    // Get the current player's location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();

    currentOrientation = Z_MINUS;



    mcpp::BlockType blockInFront = mc.getBlock(playerLoc + MOVE_XPLUS);
    mcpp::BlockType blockBehind = mc.getBlock(playerLoc + MOVE_XMINUS);
    mcpp::BlockType blockLeft = mc.getBlock(playerLoc + MOVE_ZPLUS);
    mcpp::BlockType blockRight = mc.getBlock(playerLoc + MOVE_ZMINUS);

    if (blockInFront == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        currentOrientation = X_PLUS;
    }
    else if (blockBehind == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        currentOrientation = X_MINUS;
    }
    else if (blockLeft == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        currentOrientation = Z_PLUS;
    }
    else if (blockRight == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        currentOrientation = Z_MINUS;
    }
}

void Agent::guideToExit()
{
    mcpp::MinecraftConnection mc;
    // Initialize the agent's orientation
    initializePlayerBlock();

    int step = 0;
    mcpp::Coordinate currentLocation = mc.getPlayerPosition();
    mcpp::Coordinate previousLocation = currentLocation;
    bool backtracking = false; 
    bool isValid = true;
   
    while (isValid == true)
    {
        currentOrientation = turnRight(currentOrientation);
        mcpp::Coordinate nextLocation = getNextLocation(currentLocation, currentOrientation);

        
        if (mc.getBlock(nextLocation) == mcpp::Blocks::ACACIA_WOOD_PLANK)
        {
            if (!backtracking) {
                // If a wall is encountered, turn left 
                currentOrientation = turnLeft(currentOrientation);
                backtracking = true; 
            }
            else {
                mc.doCommand("setblock " + std::to_string(previousLocation.x) + " " + std::to_string(previousLocation.y) + " " + std::to_string(previousLocation.z) + " minecraft:air");

                currentOrientation = turnBack(currentOrientation);
                backtracking = false; 
            }

            
        }
        else
        {
            // Place a LIME CARPET block at the next location
            mc.doCommand("setblock " + std::to_string(nextLocation.x) + " " + std::to_string(nextLocation.y) + " " + std::to_string(nextLocation.z) + " minecraft:lime_carpet");

            // Remove the previous LIME CARPET block
            mc.doCommand("setblock " + std::to_string(currentLocation.x) + " " + std::to_string(currentLocation.y) + " " + std::to_string(currentLocation.z) + " minecraft:air");

            // Output path coordinates to the terminal
            std::cout << "Step[" << step << "]: (" << nextLocation.x << ", " << nextLocation.y << ", " << nextLocation.z << ")\n";

            previousLocation = currentLocation;
            currentLocation = nextLocation;
            backtracking = false; 

            // Update the agent's orientation based on the new location
            currentOrientation = getNewOrientation(currentLocation, nextLocation);

            step++;
        }

        isValid = CheckIfExit(mc, currentLocation, currentOrientation); 
        


   
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool Agent::CheckIfExit(mcpp::MinecraftConnection& mc, mcpp::Coordinate currentLocation, AgentOrientation currentOrientation)
{
    mcpp::Coordinate blockInFront = getNextLocation(currentLocation, currentOrientation);
    mcpp::Coordinate blockInFrontFront = getNextLocation(blockInFront, currentOrientation);
    mcpp::Coordinate blockRight = getNextLocation(blockInFront, turnRight(currentOrientation));
    mcpp::Coordinate blockBack = getNextLocation(blockRight, turnBack(currentOrientation));

    bool frontIsAir = mc.getBlock(blockInFront) == mcpp::Blocks::AIR;
    bool frontFrontIsAir = mc.getBlock(blockInFrontFront) == mcpp::Blocks::AIR;
    bool rightIsAir = mc.getBlock(blockRight) == mcpp::Blocks::AIR;
    bool backIsAir = mc.getBlock(blockBack) == mcpp::Blocks::AIR;

    if( frontIsAir && frontFrontIsAir && rightIsAir && backIsAir)
    {
        return false;
        mc.doCommand("setblock " + std::to_string(currentLocation.x) + " " + std::to_string(currentLocation.y) + " " + std::to_string(currentLocation.z) + " minecraft:air");
        std::cout << "\n";

    }
    else 
    {
        return true;
    }
}


AgentOrientation Agent::turnLeft(AgentOrientation orientation)
{
    switch (orientation)
    {
        case X_PLUS: return Z_MINUS;
        case Z_PLUS: return X_PLUS;
        case X_MINUS: return Z_PLUS;
        case Z_MINUS: return X_MINUS;
    }
    return orientation; 
}

AgentOrientation Agent::getNewOrientation(const mcpp::Coordinate& currentLocation, const mcpp::Coordinate& nextLocation)
{
    int dx = nextLocation.x - currentLocation.x;
    int dz = nextLocation.z - currentLocation.z;

    if (dx == 1) {
        return X_PLUS;
    } else if (dx == -1) {
        return X_MINUS;
    } else if (dz == 1) {
        return Z_PLUS;
    } else if (dz == -1) {
        return Z_MINUS;
    }


    return currentOrientation;
}

mcpp::Coordinate Agent::getNextLocation(const mcpp::Coordinate& currentLocation, AgentOrientation orientation)
{
    mcpp::Coordinate nextLocation = currentLocation;

    switch (orientation) {
        case X_PLUS:
            nextLocation.z += 1; 
            break;
        case Z_PLUS:
            nextLocation.x -= 1; 
            break;
        case X_MINUS:
            nextLocation.z -= 1; 
            break;
        case Z_MINUS:
            nextLocation.x += 1; 
            break;
    }

    return nextLocation;
}

AgentOrientation Agent::turnBack(AgentOrientation orientation)
{
    switch (orientation)
    {
        case X_PLUS: return X_MINUS;
        case Z_PLUS: return Z_MINUS;
        case X_MINUS: return X_PLUS;
        case Z_MINUS: return Z_PLUS;
    }
    return orientation; 
}

AgentOrientation Agent::turnRight(AgentOrientation orientation)
{
    switch (orientation) {
        case X_PLUS:
            return Z_PLUS;
        case Z_PLUS:
            return X_MINUS;
        case X_MINUS:
            return Z_MINUS;
        case Z_MINUS:
            return X_PLUS;
    }
    return orientation; 
}