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
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -60, col) , mcpp::Blocks::DIAMOND_BLOCK);
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -59, col) , mcpp::Blocks::DIAMOND_BLOCK); //Second layer of maze
                                mc.setBlock(buildStart + mcpp::Coordinate(row, -58, col) , mcpp::Blocks::DIAMOND_BLOCK);

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
/*
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
*/

void Maze::generateRandomMaze(std::vector<std::string>& maze, int length, int width) {
    for(int row = 0; row < length; row++){
        std::string mazeRow;
        for (int col = 0; col < width; col++) {
            mazeRow += 'x';
        }
        maze.push_back(mazeRow);
    }

    int entranceX = 1 + 2 * (std::rand() % ((width - 1) / 2));
    int entranceY = 0;

    maze[entranceY][entranceX] = '.';

    int startX, startY;

    do{
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
