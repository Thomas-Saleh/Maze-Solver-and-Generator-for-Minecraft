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

void Maze::generateRandomMaze(std::vector<std::string>& maze, int length, int width){
    
    //Creates a rectangle of the specified H | W
    for(int col = 0; col < length; col++){
        std::string mazeRow;
        for(int row = 0; row < width; row++){
            mazeRow += 'x';
            if(row == width - 1){
                maze.push_back(mazeRow);
            }
        }
    }

    //Randomly choose a starting point
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int startX, startY;

    do{
        if (std::rand() % 2 == 0) {
            // Select a random edge along the top or bottom
            startX = (std::rand() % 2 == 0) ? 0 : width - 1;
            startY = std::rand() % length;
        } else {
            // Select a random edge along the left or right
            startX = std::rand() % width;
            startY = (std::rand() % 2 == 0) ? 0 : length - 1;
        }
    }
    while((startX == 0 && startY == 0) || (startX == 0 && startY == length - 1) || (startX == width - 1 && startY == 0) || (startX == width - 1 && startY == length - 1));

    maze[startX][startY] = '*';

    //Initial step into maze
        if(startX == 0){ //On left side of maze
            maze[startX + 1][startY] = '*';
            maze[startX][startY] = '.';
        }
        else if(startX == width - 1){ //On Right side
            maze[startX - 1][startY] = '*';
            maze[startX][startY] = '.';
        }

        if(startY == 0){ //Start at top
            maze[startX][startY + 1] = '*';
            maze[startX][startY] = '.';
        }
        else if(startY == length - 1){ //Start at bottom
            maze[startX][startY - 1] = '*';
            maze[startX][startY] = '.';
        }

}
