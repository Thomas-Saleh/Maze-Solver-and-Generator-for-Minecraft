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
        printStartText();
        printMainMenu();
        std::cin >> userChoice;
        if(userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4 || userChoice == 5){
            curState = ST_Exit;

            if(userChoice == 1){
                printGenerateMazeMenu();
            }
            else if(userChoice == 2){
                printGenerateMazeMenu();
            }
            else if(userChoice == 3){
                printSolveMazeMenu();
            }
            else if(userChoice == 4){
                printTeamInfo();
            }
            else{
                printExitMessage();
            }
        }
        else{
            std::cout << "Error. Input Invalid. Please enter a number from 1 to 5." << std::endl;
        }
    }
}

 


