#include <iostream>

void printStartText(void){
    std::cout << std::endl;
    std::cout << "Welcome to MineCraft MazeRunner!" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

void printMainMenu(void){
    std::cout << std::endl;
    std::cout << "------------- MAIN MENU -------------" << std::endl;
    std::cout << "1) Generate Maze" << std::endl;
    std::cout << "2) Build Maze in MineCraft" << std::endl;
    std::cout << "3) Solve Maze" << std::endl;
    std::cout << "4) Show Team Information" << std::endl;
    std::cout << "5) Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printGenerateMazeMenu(void){
    std::cout << std::endl;
    std::cout << "------------- GENERATE MAZE -------------" << std::endl;
    std::cout << "1) Read Maze from terminal" << std::endl;
    std::cout << "2) Generate Random Maze" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
   
}

void printSolveMazeMenu(void){
    std::cout << std::endl;
    std::cout << "------------- SOLVE MAZE -------------" << std::endl;
    std::cout << "1) Solve Manually" << std::endl;
    std::cout << "2) Show Escape Route" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}


void printTeamInfo(void){
    std::cout << std::endl;
    std::cout << "Team members:" << std::endl;

    //TODO: change this part to reflect your team**********
    std::cout << "\t [1] Marko Cukanic (s4008040@rmit.edu.au)" << std::endl;
    std::cout << "\t [2] Vincent Dao (s4007708@rmit.edu.au)" << std::endl;
    std::cout << "\t [3] Thomas Saleh (s4006031@rmit.edu.au)" << std::endl;
    //*************

    std::cout << std::endl;
}

void printExitMessage(void){
    std::cout << std::endl;
    std::cout << "The End!" << std::endl;
    std::cout << std::endl;
}

void readBasePoint(int& xCor, int& yCor, int& zCor) {
    std::cout << "Enter the basePoint of maze in the format [X Y Z]" << std::endl;
    std::cin >> xCor >> yCor >> zCor;
    
}

void readLengthAndWidth(int& length, int& width) {
    std::cout << "Enter the length and width of the maze [L W]" << std::endl;
    std::cin >> length >> width;
    
}

void readMazeStructure(std::vector<std::string>& maze, int length, int width) {
    std::cout << "Enter the maze structure:" << std::endl;
    for (int i = 0; i < length; ++i) {
        std::string row;
        std::cin >> row;
        if (static_cast<int>(row.size()) != width) {
            std::cout << "Invalid input. Row should have exactly " << width << " characters." << std::endl;
            i--;
        } else {
            maze.push_back(row);
        }
    }
}

void printMazeInfo(const std::vector<std::string>& maze, int baseX, int baseY, int baseZ) {
    std::cout << "Maze read successfully" << std::endl;
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "Base Point: (" << baseX << ", " << baseY << ", " << baseZ << ")" << std::endl;
    
    std::cout << "Structure:" << std::endl;
    for (const std::string& row : maze) {
        std::cout << row << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}


