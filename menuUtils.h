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
    for(int row = 0; row < width; row++){
        std::string mazeRow;
        for(int col = 0; col < length; col++){
            mazeRow += 'x';
            if(col == length - 1){
                maze.push_back(mazeRow);
            }
        }
    }

    //Randomly choose a starting point
    srand(100);

    int startX, startY;

    if(rand() % 2 == 0){
        startX = 1 + rand() % (length - 2);
        if(rand() % 2 == 0){
            startY = 0;
        } 
        else{
            startY = width - 1;
        }
    } 
    else{
        startY = 1 + rand() % (width - 2);
        if(rand() % 2 == 0){
            startX = 0;
        } 
        else{
            startX = length - 1;
        }
    }

    maze[startX][startY] = '*';

    //Carve a path
    

}

