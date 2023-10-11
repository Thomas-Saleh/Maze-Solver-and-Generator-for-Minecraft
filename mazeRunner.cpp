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
    //read Mode;

    

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
            if(userChoice == 1){
                printGenerateMazeMenu();
                std::cin >> userChoice;

                if (userChoice == 1){   
                    int baseX, baseY, baseZ;
                    readBasePoint(baseX, baseY, baseZ);

                    int mazeLength, mazeWidth;
                    readLengthAndWidth(mazeLength, mazeWidth);

                    std::vector<std::string> maze;
                    readMazeStructure(maze, mazeLength, mazeWidth);

                    printMazeInfo(maze, baseX, baseY, baseZ);

                    Maze::generateManualMaze(maze, mazeLength, mazeWidth, baseX, baseY, baseZ);

                    
                }              

                if (userChoice == 2) {
                    int baseX, baseY, baseZ;
                    readBasePoint(baseX, baseY, baseZ);

                    int mazeLength, mazeWidth;
                    readLengthAndWidth(mazeLength, mazeWidth);
                }    
            }
            else if(userChoice == 2){
                //Maze();
                
            }
            else if(userChoice == 3){
                printSolveMazeMenu();
                
            }
            else if(userChoice == 4){
                printTeamInfo();
                
            }
            else if(userChoice == 5){
                printExitMessage();
                curState = ST_Exit;

            }
            else { 
                std::cout << "Input Error: Enter a number between 1 and 5 ...." << std::endl;
                
            }
    }
}





 








 


