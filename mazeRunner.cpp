#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){

    //bool mode = NORMAL_MODE;
    //read Mode

    

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    States curState = ST_Main;
    int userChoice = 0;
    

    //State machine for menu        
    while (curState != ST_Exit)
    {
        std::cout << "Welcome to MineCraft MazeRunner!" << std::endl << "--------------------------------" << std::endl;
        
        std::cout << "------------- MAIN MENU -------------" << std::endl;
        std::cout << "1) Generate Maze" << std::endl;
        std::cout << "2) Build Maze in MineCraft" << std::endl;
        std::cout << "3) Solve Maze" << std::endl;
        std::cout << "4) Show Team Information" << std::endl;
        std::cout << "5) Exit" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Enter Menu item to continue:" << std::endl;
        std::cin >> userChoice;

        if (userChoice == 1) {
            generateMaze();
        }

        if (userChoice == 2){
            BuildMaze();
        }

        
    }
     
    printExitMessage();


    return EXIT_SUCCESS;

}

static void printExitMessage() {
    std::cout << "**End Printing Maze**";

}

static void generateMaze() {
    //generate maze
}

static void BuildMaze(){

}