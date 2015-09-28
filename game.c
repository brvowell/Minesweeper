// Game Functions
// Project 4: Minesweeper
// Brandon Vowell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int left(char **, int, int);
int upLeft(char **, int, int);
int up(char **, int, int);
int upRight(char **, int, int, int);
int right(char **, int, int, int);
int downRight(char **, int, int, int, int);
int down(char **, int, int, int);
int downLeft(char **, int, int, int);

char **createBoard(int width, int height)    {
    // Creates the mine and status boards based on inputted width and height
    char **board = malloc(sizeof(char *) * width);
    int w;
    for(w = 0; w < width; w++) {
        board[w] = malloc(sizeof(char) * height);
    }

    int h;
    h = 0;
    while(h < height)   {
        w = 0;
        while(w < width)     {
            board[w][h] = ' ';
            w++;
        }
        h++;
    }
    return board;
}

void setMines(char **mines, int width, int height, int number)    {
    int n = 0;
    int h, w;
    while(n < number)   {
        w = rand() % width;
        h = rand() % height;
        // Sets bomb locations
        while(mines[w][h] == '@')   {
            w = rand() % width;
            h = rand() % height;
        // If duplicate location, continues to assign locations until open space is found
        }
        mines[w][h] = '@';
        n++;
    }

    return;
}

void setStatus(char **status, int width, int height)  {
    int h = 0;
    while(h < height)    {
        int w = 0;
        while(w < width)    {
            status[w][h] = '-';
            w++;
        }
        h++;
    }

    return;
}

char minesAroundLocation(char **mines, int w, int h, int width, int height)  {
    int near;
    char current = mines[w][h];
    if(current == '@')
        return current;
    // Takes the values from the 8 helper functions to deterimine the number of 
    // adjacent bombs
    else    {
        near = left(mines, w, h) + upLeft(mines, w, h) + up(mines, w, h) + \
        upRight(mines, w, h, width) + right(mines, w, h, width) + \
        downRight(mines, w, h, width, height) + down(mines, w, h, height) + \
        downLeft(mines, w, h, height);

    }
    if(near == 0)
        return ' ';

    return (char)(near + 48);
}

/*The following eight helper functions check to see if there is a bomb in 
one of the eight surrounding locations of a particular square. If there is,
each function returns 1. Otherwise, it returns 0.
*/

int left(char **mines, int w, int h)    {
    if(w != 0)
        if(mines[w-1][h] == '@')
            return 1;
    return 0;
}

int upLeft(char **mines, int w, int h)  {
    if(w != 0 && h != 0)
        if(mines[w-1][h-1] == '@')
            return 1;
    return 0;
}

int up(char** mines, int w, int h)  {
    if(h != 0)
        if(mines[w][h-1] == '@')
            return 1;
    return 0;
}

int upRight(char **mines, int w, int h, int width)  {
    if(w != width - 1 && h != 0)
        if(mines[w+1][h-1] == '@')
            return 1;
    return 0;
}

int right(char **mines, int w, int h, int width)    {
    if(w != width - 1)
        if(mines[w+1][h] == '@')
            return 1;
    return 0;
}

int downRight(char **mines, int w, int h, int width, int height) {
    if(w != width - 1 && h != height - 1)
        if(mines[w+1][h+1] == '@')
            return 1;
    return 0;
}

int down(char **mines, int w, int h, int height)    {
    if(h != height - 1) 
        if(mines[w][h+1] == '@')
            return 1;
    return 0;
}

int downLeft(char **mines, int w, int h, int height)    {
    if(w != 0 && h != height - 1)
        if(mines[w-1][h+1] == '@')
            return 1;
    return 0;
}

void numberFill(char **mines, int width, int height)   {
    // Takes the numbers from the "minesAroundLocation" function and assigns
    // them to the corresponding mine board location.
    int w = 0;
    while(w < width)    {
        int h = 0;
        while(h < height)   {
            mines[w][h] = minesAroundLocation(mines, w, h, width, height);
            h++;
        }
        w++;
    }
    return;
}


void uncoverSquares(char **composite, char **mines, char **status, int width, \
int height, int w, int h)    {

    // If the space to be uncovered has no adjacent mines, this function checks the 
    // adjacent spaces using recursion and ,if they also don't have any nearby mines, 
    // uncovers those spaces. It also uncovers the first row of numbers because it is 
    // impossible for them to be bombs. 
    composite[w][h] = mines[w][h];
    status[w][h] = ' ';
    if(composite[w][h] == ' ')  {
        if(w < width - 1 && mines[w+1][h] == ' ' && status[w+1][h] == '-'){ 
            uncoverSquares(composite, mines, status, width, height, w+1, h);
        }
        if(w > 0 && mines[w-1][h] == ' ' && status[w-1][h] == '-')   {
            uncoverSquares(composite, mines, status, width, height, w-1, h);
        }
        if(h < height - 1 && mines[w][h+1] == ' ' && status[w][h+1] == '-')  {
            uncoverSquares(composite, mines, status, width, height, w, h+1);
        }
        if(h > 0 && mines[w][h-1] == ' ' && status[w][h-1] == '-')   {
            uncoverSquares(composite, mines, status, width, height, w, h-1);
        }
        if(w < width - 1 && (int)mines[w+1][h] > '0' && (int)mines[w+1][h] < '9' \
        && status[w+1][h] == '-')  {

            composite[w+1][h] = mines[w+1][h];
            status[w+1][h] = ' ';
        }
        if(w > 0 && (int)mines[w-1][h] > '0' && (int)mines[w-1][h] < '9' && status[w-1][h] == '-'){
            composite[w-1][h] = mines[w-1][h];
            status[w-1][h] = ' ';
        }
        if(h < height - 1 && (int)mines[w][h+1] > '0' && (int)mines[w][h+1] < '9' \
        && status[w][h+1] == '-') {

            composite[w][h+1] = mines[w][h+1];
            status[w][h+1] = ' ';
        }
        if(h > 0 && (int)mines[w][h-1] > '0' && (int)mines[w][h-1] < '9' && status[w][h-1] == '-') {
            composite[w][h-1] = mines[w][h-1];
            status[w][h-1] = ' ';
        }
    }
} 

