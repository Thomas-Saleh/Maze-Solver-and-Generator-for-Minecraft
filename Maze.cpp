#include "Maze.h"
#include <random>

#include <chrono>
#include <thread>


Maze::Maze(){
}

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen, bool mode){
}

Maze::~Maze(){
}



void Maze::buildMaze(const std::vector<std::string>& maze, int length, int width, mcpp::Coordinate buildStart){
    mcpp::MinecraftConnection mc; 
    
    for(int row = 0; row < length; row++){
                        for(int col = 0; col < width; col++){
                            if(maze[row][col] == 'x'){
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::DIAMOND_BLOCK);
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -59, col) , mcpp::Blocks::DIAMOND_BLOCK); //Second layer of maze
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -58, col) , mcpp::Blocks::DIAMOND_BLOCK);

                            }
                            else{
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::AIR);
                            }

                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        }
                    }
}

void Maze::teleportPlayerToRandomDot(const std::vector<std::string>& maze) {
    mcpp::MinecraftConnection mc; 

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<std::vector<std::string>::size_type, std::string::size_type>> dotCoordinates;

    for (std::vector<std::string>::size_type row = 0; row < maze.size(); row++) {
        for (std::string::size_type col = 0; col < maze[row].size(); col++) {
            if (maze[row][col] == '.') {
                dotCoordinates.push_back(std::make_pair(row, col));
            }
        }
    }

    if (dotCoordinates.empty()) {
        std::cout << "No '.' cells found in the maze." << std::endl;
        return; 
    }

    std::uniform_int_distribution<std::vector<std::string>::size_type> distribution(0, dotCoordinates.size() - 1);
    std::vector<std::string>::size_type randomIndex = distribution(gen);

    std::vector<std::string>::size_type selectedRow = dotCoordinates[randomIndex].first;
    std::string::size_type selectedCol = dotCoordinates[randomIndex].second;

    std::string playerName = "@a";
    std::string tpCommand = "tp " + playerName + " " + std::to_string(selectedRow) + " -60 " + std::to_string(selectedCol);
     mc.doCommand(tpCommand);
}
