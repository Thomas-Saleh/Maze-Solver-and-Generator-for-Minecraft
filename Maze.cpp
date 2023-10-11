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

void Maze::generateManualMaze(const std::vector<std::string>& maze, int length, int width, mcpp::Coordinate buildStart){
    mcpp::MinecraftConnection mc; 
    
    for(int row = 0; row < length; row++){
                        for(int col = 0; col < width; col++){
                            if(maze[row][col] == 'x'){
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::DIAMOND_BLOCK);
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -59, col) , mcpp::Blocks::DIAMOND_BLOCK); //Second layer of maze
                            }
                            else{
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::AIR);
                            }

                            //std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        }
                    }
}