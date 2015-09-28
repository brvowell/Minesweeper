// Final Product
// Project 4: Minesweeper
// Brandon Vowell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "io.h"

// This file contains the main function and the game loop titled "runProgram"

void runProgram(char **, char **, int, int);

int main(int argc,char *argv[])    {

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int number = atoi(argv[3]);
    char **mine = createBoard(width, height);
    setMines(mine, width, height, number);
    char **status = createBoard(width, height);
    numberFill(mine, width, height);
    setStatus(status, width, height);
    printBoard(status, width, height);
    
    runProgram(mine, status, width, height);
    
    return 0;
}


void runProgram(char ** mine, char ** status,  int width, int height)  {

    int w, h;
    char **composite;
    int endGame = 0;
    while(endGame != 1)    {
        // Takes in original move. If invalid, changed in "placeMove" function
        printf("Which square do you wish to uncover?\n");
        printf("Enter a row and column: ");
        scanf(" %d %d", &h, &w);
        placeMove(status, width, height, w, h);
        system("clear");
        composite = makeCompositeBoard(mine, status, width, height);
        uncoverSquares(composite, mine, status, width, height, w, h);
        printf("     -------MINESWEEPER-------\n");
        printBoard(composite, width, height);
        printf("\n");
        endGame = boardClear(status, mine, width, height);
        // If there is a winner, the game loop breaks and prints out winning statement
        if(endGame == 1)
            break;
        endGame = bombChosen(composite, width, height);
        // If a bomb is chosen, "endGame" changes to 1 and the loop breaks
    }
}
