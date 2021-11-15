#include <iostream>
using namespace std;

const int UNIT = 8; //Tamaño de caja en la tabla
const int TWaH = (5*UNIT)+1; //Table Width and Height
int Xant = 3, Yant = 3; // X anterior, Y anterior
bool playerMoved;
int highlightedCoordX = 0, highlightedCoordY = 0;

struct player {
    string name;
    string color;
    int captured_pieces;
};

string colorP1;
string colorP2;

int moves = 0;
string message;
string currentPos;
string lastPos;
string highlightedCoords;
string playerTurnMsg;

int grid[TWaH][TWaH] = {
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
};

int gridStats[5][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};

int gridBackground[5][5] = {
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1}
};

string interperate(int num) {
    string re; //vaiable to REturn
    switch(num) {
        case 0:
            re = "!!"; //#c7c7c7 - light square color
            break;
        case 1:
            re = "OO"; //#751616 - dark square color
            break;
        case 2:
            re = colorP1; //#xxxxxx - player chooses color
            break;
        case 3:
            re = colorP2; //#xxxxxx - player chooses color
            break;
        case 7:
            re = "  "; //#fcdf00 - selector color
            break;
        case 8:
            re = "+ "; //#0000ff - highlight color
            break;
        case 9:
            re = "=="; //#000000 - black border color
            break;
        default:
            re = "/\\";
            break;
    }
    return re;
}

void printGrid() {
    for(int j=0; j<TWaH; j++) {
        for(int i=0; i<TWaH; i++) {
            cout << interperate(grid[j][i]);
        }
        cout << "\t\t";
        switch(j) {
            case 0:
                cout << "Moves made: " << moves;
                break;
            case 1:
                cout << currentPos;
                break;
            case 2:
                cout << lastPos;
                break;
            case 3:
                cout << highlightedCoords;
                break;
            case 4:
                cout << playerTurnMsg;
                break;
            case 6:
                for(int i=0; i<5; i++) cout << "[" << gridStats[0][i] << "] "; break;
            case 7:
                for(int i=0; i<5; i++) cout << "[" << gridStats[1][i] << "] "; break;
            case 8:
                for(int i=0; i<5; i++) cout << "[" << gridStats[2][i] << "] "; break;
            case 9:
                for(int i=0; i<5; i++) cout << "[" << gridStats[3][i] << "] "; break;
            case 10:
                for(int i=0; i<5; i++) cout << "[" << gridStats[4][i] << "] "; break;
            case 13:
                cout << message;
                break;
        }
        cout << endl;
    }
}

void selectSquare(int x, int y) {
    int startPosX = UNIT * (x-1);
    int startPosY = UNIT * (y-1);
    for(int i=0; i<9; i++) {
        grid[startPosX][startPosY + i] = 7;
        grid[startPosX + i][startPosY] = 7;
        grid[startPosX + i][startPosY + UNIT] = 7;
        grid[startPosX + UNIT][startPosY + i] = 7;
    }
}

void revertSquare(int x, int y) {
    int startPosX = UNIT * (x-1);
    int startPosY = UNIT * (y-1);
    for(int i=0; i<9; i++) {
        grid[startPosX][startPosY + i] = 9;
        grid[startPosX + i][startPosY] = 9;
        grid[startPosX + i][startPosY + UNIT] = 9;
        grid[startPosX + UNIT][startPosY + i] = 9;
    }
}

void drawPiece(int p, int x, int y) {
    int player;
    int startPosX = UNIT * (x-1) + 2;
    int startPosY = UNIT * (y-1) + 2;
    switch(p) {
        case 1:
            player = 2;
            break;
        case 2:
            player = 3;
            break;
    }
    for(int j=0; j<5; j++) {
        for(int i=0; i<5; i++) {
            if(j == 0 && i == 0) {
            }else if(j == 0 && i == 4) {
            } else if(j == 4 && i == 0) {
            } else if(j == 4 && i == 4) {
            } else {
                grid[startPosX + j][startPosY + i] = player;
            }
        }
    }
}

void errasePiece(int x, int y) {
    int startPosX = UNIT * (x-1) + 2;
    int startPosY = UNIT * (y-1) + 2;
    for(int j=0; j<5; j++) {
        for(int i=0; i<5; i++) {
            grid[startPosX + j][startPosY + i] = gridBackground[x-1][y-1];
        }
    }
}

void highlightSquare(int x, int y) {
    int startPosX = UNIT * (x-1) + 1;
    int startPosY = UNIT * (y-1) + 1;
    for(int j=0; j<7; j++) {
        for(int i=0; i<7; i++) {
            if(grid[startPosX+j][startPosY+i] != 2 && grid[startPosX+j][startPosY+i] != 3) {
                grid[startPosX+j][startPosY+i] = 8;
            }
        }
    }
}

void unHighlightSquare(int x, int y) {
    int startPosX = UNIT * (x-1) + 1;
    int startPosY = UNIT * (y-1) + 1;
    if(x != 0 && y != 0) {
        for(int j=0; j<7; j++) {
            for(int i=0; i<7; i++) {
                if(grid[startPosX+j][startPosY+i] != 2 && grid[startPosX+j][startPosY+i] != 3) {
                    grid[startPosX+j][startPosY+i] = gridBackground[x-1][y-1];
                }
            }
        }
    }
}

void move(int p, int *x, int *y) {
    char key;
    Xant = *x;
    Yant = *y;
    cin >> key;
    switch(key) {
        case 'w':
            if(*x != 1) *x = *x - 1;
            break;
        case 'a':
            if(*y != 1) *y = *y - 1;
            break;
        case 's':
            if(*x != 5) *x = *x + 1;
            break;
        case 'd':
            if(*y != 5) *y = *y + 1;
            break;
        case 'p':
            if(gridStats[*x-1][*y-1] == 0) {
                moves++;
                drawPiece(p,*x,*y);
                gridStats[*x-1][*y-1] = p;
                playerMoved = true;
                message = "";
            } else {
                message = "You can't place a piece on top of another.";
            }
            break;
        case 'm':
            if(gridStats[*x-1][*y-1] == p) {
                unHighlightSquare(highlightedCoordX, highlightedCoordY);
                highlightedCoordX = *x;
                highlightedCoordY = *y;
                highlightSquare(*x, *y);
                message = "";
            } else if(gridStats[*x-1][*y-1] == 0) {
                message = "You can't select an empty square.";
            } else {
                message = "You can't select your opponents piece.";
            }
            break;
        case 'n':
            if(gridStats[*x-1][*y-1] != 1 && gridStats[*x-1][*y-1] != 2) {
                if((abs(*x - highlightedCoordX) == 1 && abs(*y - highlightedCoordY) == 0) || (abs(*x - highlightedCoordX) == 0 && abs(*y - highlightedCoordY) == 1)) {
                    moves++;
                    message = "";
                    gridStats[*x-1][*y-1] = p;
                    gridStats[highlightedCoordX-1][highlightedCoordY-1] = 0;
                    drawPiece(p, *x, *y);
                    unHighlightSquare(highlightedCoordX, highlightedCoordY);
                    errasePiece(highlightedCoordX, highlightedCoordY);
                    playerMoved = true;
                    highlightedCoordX = 0;
                    highlightedCoordY = 0;
                } else {
                    message = "You can only move to a square dirrectly above, bellow or to the sides of your selected piece.";
                }
            } else {
                message = "You can't move a piece on top of another.";
            }
    }
}

int main() {
    bool play = true;
    int playerTurn = 1;
    int X = 3, Y = 3;
    int *ptrX = &X;
    int *ptrY = &Y;
    player player1;
    player player2;

    player1.color = "1 ";
    player2.color = "2 ";

    colorP1 = player1.color;
    colorP2 = player2.color;

    while(play) {

        //---
        currentPos = "Current position: " + to_string(X) + ", " + to_string(Y);
        lastPos = "Last position: " + to_string(Xant) + ", " + to_string(Yant);
        highlightedCoords = "Highlighted coordinates: " + to_string(highlightedCoordX) + ", " + to_string(highlightedCoordY);
        playerTurnMsg = "Player " + to_string(playerTurn) + "'s turn.";
        //---

        playerMoved = false;
        selectSquare(X,Y);
        printGrid();
        move(playerTurn, ptrX, ptrY);
        revertSquare(Xant, Yant);
        if(playerMoved) {
            switch(playerTurn) {
                case 1:
                    playerTurn = 2;
                    break;
                case 2:
                    playerTurn = 1;
                    break;
            }
        }
    }
}
