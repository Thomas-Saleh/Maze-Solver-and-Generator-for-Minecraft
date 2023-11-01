#include "Maze.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>


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
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::ACACIA_WOOD_PLANK);
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -59, col) , mcpp::Blocks::ACACIA_WOOD_PLANK); //Second layer of maze
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -58, col) , mcpp::Blocks::ACACIA_WOOD_PLANK);

                            }
                            else{
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::AIR);
                            }

                            std::this_thread::sleep_for(std::chrono::milliseconds(250));
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


void Maze::generateRandomMaze(std::vector<std::string>& maze, int length, int width) {
    for (int row = 0; row < length; row++) {
        std::string mazeRow;
        for (int col = 0; col < width; col++) {
            mazeRow += 'x';
        }
        maze.push_back(mazeRow);
    }

    int side = std::rand() % 4;
    
    int entranceX = 0;
    int entranceY = 0;

    switch (side) {
        case 0:  // North
            entranceX = 1 + 2 * (std::rand() % ((width - 1) / 2));
            entranceY = 0;
            break;
        case 1:  // South
            entranceX = 1 + 2 * (std::rand() % ((width - 1) / 2));
            entranceY = length - 1;
            break;
        case 2:  // East
            entranceX = width - 1;
            entranceY = 1 + 2 * (std::rand() % ((length - 1) / 2));
            break;
        case 3:  // West
            entranceX = 0;
            entranceY = 1 + 2 * (std::rand() % ((length - 1) / 2));
            break;
    }

    maze[entranceY][entranceX] = '.';

    int startX, startY;

    do {
        startX = 1 + 2 * (std::rand() % ((width - 1) / 2));
        startY = 1 + 2 * (std::rand() % ((length - 1) / 2));
    } while (startX % 2 == 0 || startY % 2 == 0);

    recursiveBacktrack(maze, length, width, startX, startY);
}




void Maze::recursiveBacktrack(std::vector<std::string>& maze, int length, int width, int x, int y) {
    const int dx[] = {0, 0, -2, 2};
    const int dy[] = {2, -2, 0, 0};
    const int directions = 4;

    maze[y][x] = '.';

    int dir[directions] = {0, 1, 2, 3};
    std::mt19937 gen(std::random_device{}());
    std::shuffle(dir, dir + directions, gen);

    for(int i = 0; i < directions; i++){
        int nx = x + dx[dir[i]];
        int ny = y + dy[dir[i]];

        if(nx >= 1 && nx < width - 1 && ny >= 1 && ny < length - 1 && maze[ny][nx] == 'x'){
            int mx = (x + nx) / 2;
            int my = (y + ny) / 2;
            maze[my][mx] = '.';
            recursiveBacktrack(maze, length, width, nx, ny);
        }
    }
}
