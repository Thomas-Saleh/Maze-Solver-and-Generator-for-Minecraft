#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>

void printTextWithDelay(const std::string& text, int delay_ms) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    std::cout << std::endl;
}
#include <cstdlib>
#include <ctime>

void printStartText(void) {
    std::cout << std::endl;
    printTextWithDelay("Welcome to MineCraft MazeRunner!", 50); 
    printTextWithDelay("--------------------------------", 20);
}

void printMainMenu(void) {
    std::cout << std::endl;
    printTextWithDelay("------------- MAIN MENU -------------", 20);
    printTextWithDelay("1) Generate Maze", 20);
    printTextWithDelay("2) Build Maze in MineCraft", 20);
    printTextWithDelay("3) Solve Maze", 20);
    printTextWithDelay("4) Show Team Information", 20);
    printTextWithDelay("5) Exit", 20);
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printGenerateMazeMenu(void) {
    std::cout << std::endl;
    printTextWithDelay("------------- GENERATE MAZE -------------", 20);
    printTextWithDelay("1) Read Maze from terminal", 20);
    printTextWithDelay("2) Generate Random Maze", 20);
    printTextWithDelay("3) Back", 20);
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printSolveMazeMenu(void) {
    std::cout << std::endl;
    printTextWithDelay("------------- SOLVE MAZE -------------", 20);
    printTextWithDelay("1) Solve Manually", 20);
    printTextWithDelay("2) Show Escape Route", 20);
    printTextWithDelay("3) Back", 20);
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printTeamInfo(void) {
    std::cout << std::endl;
    printTextWithDelay("Team members:", 50);

    // TODO: change this part to reflect your team
    printTextWithDelay("\t [1] Marko Cukanic (s4008040@rmit.edu.au)", 20);
    printTextWithDelay("\t [2] Vincent Dao (s4007708@rmit.edu.au)", 20);
    printTextWithDelay("\t [3] Thomas Saleh (s4006031@rmit.edu.au)", 20);
    // *************

    std::cout << std::endl;
}

void printExitMessage(void) {
    std::cout << std::endl;
    printTextWithDelay("The End!", 50);
    std::cout << std::endl;
}

void readBasePoint(int& xCor, int& yCor, int& zCor) {
    printTextWithDelay("Enter the basePoint of maze in the format [X Y Z]", 50);
    std::cin >> xCor >> yCor >> zCor;
}

void readLengthAndWidth(int& length, int& width) {
    printTextWithDelay("Enter the length and width of the maze [L W]", 50);
    std::cin >> length >> width;
}

void readMazeStructure(std::vector<std::string>& maze, int length, int width) {
    printTextWithDelay("Enter the maze structure:", 50);
    for (int i = 0; i < length; ++i) {
        std::string row;
        std::cin >> row;
        if (static_cast<int>(row.size()) != width) {
            printTextWithDelay("Invalid input. Row should have exactly " + std::to_string(width) + " characters.", 50);
            i--;
        } else {
            maze.push_back(row);
        }
    }
}

void printMazeInfo(const std::vector<std::string>& maze, int baseX, int baseY, int baseZ) {
    printTextWithDelay("Maze read successfully", 50);
    printTextWithDelay("**Printing Maze**", 50);
    printTextWithDelay("Base Point: (" + std::to_string(baseX) + ", " + std::to_string(baseY) + ", " + std::to_string(baseZ) + ")", 50);

    printTextWithDelay("Structure:", 50);
    for (const std::string& row : maze) {
        printTextWithDelay(row, 50);
    }
    printTextWithDelay("**End Printing Maze**", 50);
}

void generateRandomMaze(std::vector<std::string>& maze, int length, int width){
    
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
    

    
    //Carving a path
    //int xPos, yPos;

    //Initial step into maze
        if(startX == 0){ //On left side of maze
            maze[startX + 1][startY] = '*';
        }
        else if(startX == width - 1){ //On Right side
            maze[startX - 1][startY] = '*';
        }

        if(startY == 0){ //Start at top
            maze[startX][startY + 1] = '*';
        }
        else if(startY == length - 1){ //Start at bottom
            maze[startX][startY - 1] = '*';
        }

}

