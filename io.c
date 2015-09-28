// Game I/O functions
// Project 4: Minesweeper
// Brandon Vowell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBoard(char **board, int width, int height)    {
    int h, w;
    int i = 0;
    // Prints column numbers with correct spacing
    printf("    %d", i);  
    i++;
    while(i < width)    {
        printf("  %d" , i);
        i++;
    }
    printf("\n");
    for(h = 0; h < height; h++)   {
        // Prints row numbers with correct spacing
        printf("%d  ", h);
        w = 0;
        while(w < width)    {
            printf("{%c}", board[w][h]);
            w++;
        }
        printf("\n");
    } 
    return;
}

char **makeCompositeBoard(char **mines, char **status, int width, int height)    {
    char **composite = malloc(sizeof(char *) * width);
    int w = 0;
    while(w < width)    {
        composite[w] = malloc(sizeof(char) * height);
        w++;
    }
    int h = 0;
    // Makes a board that either prints the covered status square of the
    // corresponding square on the mine board
    while(h < height)   {
        w = 0;
        while(w < width)    {
            if(status[w][h] == '-')
                composite[w][h] = status[w][h];
            else
                composite[w][h] = mines[w][h];
            w++;
        }
        h++;
    }
    return composite;
}

void placeMove(char **status, int width, int height, int w, int h)    {
    while(w < 0 || w > width - 1 || h < 0 || h > height - 1)    {
        // If move is invalid, asks user until valid move is entered
        printf("Invalid move, try again!\n");
        printf("Which square do you wish to uncover?\n");
        printf("Enter a row and column: ");
        scanf(" %d %d", &w, &h);
    }
    status[w][h] = ' ';
    return;
}

int bombChosen(char **composite, int width, int height) {
    int endGame = 0;
    int w, h;
    for(h = 0; h < height; h++) {
        for(w = 0; w < width; w++)  {
            if(composite[w][h] == '@')  {
                // Design is made to be centered on a 10 x 10 board
                printf("\t/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
                printf("\t/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
                printf("\t/\\/\\/\\/\\BOOM!/\\/\\/\\/\n");
                printf("\t/\\/\\/\\YOU LOSE!\\/\\/\\\n");
                printf("\t/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n\n");
                endGame = 1;
            }
        }
    }
    return endGame;
}

int boardClear(char **status, char ** mine, int width, int height) {
    int endGame = 0;
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++)  {
            if(status[w][h] == '-' && mine[w][h] != '@') {
                return endGame;
            }
        }
    }
    // Design is made to be centered on a 10 x 10 board
    printf("\t/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
    printf("\t/\\/\\/\\/\\YOU/\\/\\/\\/\\/\\\n");
    printf("\t/\\/\\/\\/\\ARE/\\/\\/\\/\\/\\\n");
    printf("\t/\\/\\/\\/\\/A\\/\\/\\/\\/\\/\\\n");
    printf("\t/\\/\\/\\/WINNER!/\\/\\/\\/\n");
    printf("\t/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n\n");
    endGame = 1;
    return endGame;
}


