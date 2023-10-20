#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <iostream>
#include <vector>
#include <mcpp/mcpp.h>

class Maze
{

public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen, bool mode);
    Maze();
    ~Maze();
    void buildMaze(const std::vector<std::string>& maze, int length, int width, mcpp::Coordinate buildStart);
    void teleportPlayerToRandomDot(const std::vector<std::string>& maze);
    void generateRandomMaze(std::vector<std::string>& maze, int length, int width);
    void recursiveBacktrack(std::vector<std::string>& maze, int length, int width, int x, int y);

private:
    /* data */

};




#endif //ASSIGN_MAZE_H
