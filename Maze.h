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
    void generateManualMaze(const std::vector<std::string>& maze, int length, int width, mcpp::Coordinate buildStart);

private:
    /* data */

};




#endif //ASSIGN_MAZE_H
