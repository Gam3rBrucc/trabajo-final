#include <iostream>
using namespace std;

const int UNIT = 8; //Tamaño de caja en la tabla
const int LADT = (5*UNIT)+1; //Largo y Ancho De Tabla
int Xant = 3, Yant = 3; // X anterior, Y anterior
bool playerMoved;
int highlightedCoordX = 0, highlightedCoordY = 0;

struct player {
    string nombre;
    string color;
    int fichas_capturadas;
};

string colorJ1;
string colorJ2;

int grid[LADT][LADT] = {
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

string interpretar(int num) {
    string re; //variable para REtornar
    switch(num) {
        case 0:
            re = "!!"; //#c7c7c7 - light square color
            break;
        case 1:
            re = "OO"; //#751616 - dark square color
            break;
        case 2:
            re = colorJ1; //#xxxxxx - jugador elige color
            break;
        case 3:
            re = colorJ2; //#xxxxxx - jugador elige color
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
            re = "  ";
            break;
    }
    return re;
}

void printGrid() {
    for(int j=0; j<LADT; j++) {
        for(int i=0; i<LADT; i++) {
            cout << interpretar(grid[j][i]);
        }
        cout << endl;
    }
}

void cuadroSeleccion(int x, int y) {
    int startPosX = UNIT * (x-1);
    int startPosY = UNIT * (y-1);
    for(int i=0; i<9; i++) {
        grid[startPosX][startPosY + i] = 7;
        grid[startPosX + i][startPosY] = 7;
        grid[startPosX + i][startPosY + UNIT] = 7;
        grid[startPosX + UNIT][startPosY + i] = 7;
    }
}

void revertirCuadro(int x, int y) {
    int startPosX = UNIT * (x-1);
    int startPosY = UNIT * (y-1);
    for(int i=0; i<9; i++) {
        grid[startPosX][startPosY + i] = 9;
        grid[startPosX + i][startPosY] = 9;
        grid[startPosX + i][startPosY + UNIT] = 9;
        grid[startPosX + UNIT][startPosY + i] = 9;
    }
}

void drawPlayer(int p, int x, int y) {
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

void borrarFicha(int x, int y) {
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

void mover(int p, int *x, int *y) {
    char tecla;
    Xant = *x;
    Yant = *y;
    cin >> tecla;
    switch(tecla) {
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
                drawPlayer(p,*x,*y);
                gridStats[*x-1][*y-1] = p;
                playerMoved = true;
            }
            break;
        case 'm':
            if(gridStats[*x-1][*y-1] == p) {
                unHighlightSquare(highlightedCoordX, highlightedCoordY);
                highlightedCoordX = *x;
                highlightedCoordY = *y;
                highlightSquare(*x, *y);
            }
            break;
        case 'n':
            if(gridStats[*x-1][*y-1] != 1 && gridStats[*x-1][*y-1] != 2) {
                if((abs(*x - highlightedCoordX) == 1 && abs(*y - highlightedCoordY) == 0) || (abs(*x - highlightedCoordX) == 0 && abs(*y - highlightedCoordY) == 1)) {
                    gridStats[*x-1][*y-1] = p;
                    gridStats[highlightedCoordX-1][highlightedCoordY-1] = 0;
                    drawPlayer(p, *x, *y);
                    unHighlightSquare(highlightedCoordX, highlightedCoordY);
                    borrarFicha(highlightedCoordX, highlightedCoordY);
                    playerMoved = true;
                    highlightedCoordX = 0;
                    highlightedCoordY = 0;
                }
            }
    }
}

//temporary funcion
void printGridStats() {
    for(int j=0; j<5; j++) {
        for(int i=0; i<5; i++) {
            cout << "[" << gridStats[j][i] << "] ";
        }
        cout << endl;
    }
}


int main() {
    bool play = true;
    int playerTurn = 1;
    int X = 3, Y = 3;
    int *ptrX = &X;
    int *ptrY = &Y;
    player jugador1;
    player jugador2;

    jugador1.color = "1 ";
    jugador2.color = "2 ";

    colorJ1 = jugador1.color;
    colorJ2 = jugador2.color;

    while(play) {
        playerMoved = false;
        cuadroSeleccion(X,Y);
        printGrid();
        mover(playerTurn, ptrX, ptrY);
        revertirCuadro(Xant, Yant);
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
        //---
        printGridStats();
        cout << "Current pos:" << X << " " << Y << endl;
        cout << "Last pos:" << Xant << " " << Yant << endl;
        cout << "Highlighted pos:" << highlightedCoordX << " " << highlightedCoordY << endl;
        cout << "Player " << playerTurn << "'s turn." << endl;
        //---
    }
}
