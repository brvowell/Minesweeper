// Game Function Definitions
// Project 4: Minesweeper
// Brandon Vowell

char **createBoard(int, int);
void setMines(char **, int, int, int);
void setStatus(char **, int, int);
char minesAroundLocation(char **, int, int, int, int);
void numberFill(char **, int, int);
void uncoverSquares(char **, char **, char **, int, int ,int, int);
