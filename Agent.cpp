#include "Agent.h" 

Agent::Agent(mcpp::Coordinate startLoc)
{


}

Agent::~Agent()
{

}

void Agent::initializePlayerBlock() {
    mcpp::MinecraftConnection mc;
    // Get the current player's location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();


    
    // Assume the initial orientation with the right hand touching a wall
    // Check adjacent blocks to determine the orientation
    mcpp::BlockType blockInFront = mc.getBlock(playerLoc + MOVE_XPLUS);
    mcpp::BlockType blockBehind = mc.getBlock(playerLoc + MOVE_XMINUS);
    mcpp::BlockType blockLeft = mc.getBlock(playerLoc + MOVE_ZPLUS);
    mcpp::BlockType blockRight = mc.getBlock(playerLoc + MOVE_ZMINUS);

    if (blockInFront == mcpp::Blocks::DIAMOND_BLOCK) {
        // Initialize the orientation with the right hand facing the wall in front
        currentOrientation = X_PLUS;
    } else if (blockBehind == mcpp::Blocks::DIAMOND_BLOCK) {
        // Initialize the orientation with the right hand facing the wall behind
        currentOrientation = X_MINUS;
    } else if (blockLeft == mcpp::Blocks::DIAMOND_BLOCK) {
        // Initialize the orientation with the right hand facing the wall on the left
        currentOrientation = Z_PLUS;
    } else if (blockRight == mcpp::Blocks::DIAMOND_BLOCK) {
        // Initialize the orientation with the right hand facing the wall on the right
        currentOrientation = Z_MINUS;
    } else {
        // Handle special case when no walls are detected; you can set a default orientation
        currentOrientation = X_PLUS;
    }
}