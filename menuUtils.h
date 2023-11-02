#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <cctype>
//Adds a delay when printing each character
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
    printTextWithDelay("\t [1] Marko Cukanic (s4008040@student.rmit.edu.au)", 20);
    printTextWithDelay("\t [2] Vincent Dao (s4007708@student.rmit.edu.au)", 20);
    printTextWithDelay("\t [3] Thomas Saleh (s4006031@student.rmit.edu.au)", 20);
    // *************

    std::cout << std::endl;
}

void printExitMessage(void) {
    std::cout << std::endl;
    printTextWithDelay("The End!", 50);
    std::cout << std::endl;
}



void readBasePoint(int& xCor, int& yCor, int& zCor) {
    std::string input;
    bool validInput = false;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    printTextWithDelay("Enter the basePoint of maze in the format 'X Y Z': ", 50);

    while (!validInput) {
        std::getline(std::cin, input);
        

      
        std::istringstream ss(input);

        if (ss >> xCor >> yCor >> zCor && ss.eof()) {
            printTextWithDelay("Press Enter again", 50);
            validInput = true;
        } else {
            std::cout << "Invalid input. Please enter the format 'X Y Z'." << std::endl;
        }
    }
}

void readLengthAndWidth(int& length, int& width) {
    std::string input;
    bool validInput = false;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printTextWithDelay("Enter the length and width of the maze 'L W': ", 50);

    while (!validInput) {

        std::getline(std::cin, input);

        std::stringstream ss(input);

        if (ss >> length && ss.get() == ' ' && ss >> width && ss.eof()) {
            if (length > 0 && width > 0) {
                validInput = true;
            } else {
                std::cout << "Both inputs must be positive integers." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter the format [L W] with positive integers." << std::endl;
        }
    }
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



