#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
using namespace System;

const int UNIT = 8; // Size of a square
const int TWaH = (5 * UNIT) + 1; // Board Width and Height
int Xant = 3, Yant = 3; // X anterior, Y anterior
int xHighlight = 0, yHighlight = 0;
bool playerMoved;

struct player {
    string name;
    int color;
    int captured_pieces;
    int moves = 0;
};

player p1;
player p2;

int moves = 0;
string message1;
string message2;
string playerTurnMsg;

char available_colors[5] = {'A','B','V','M','R'};

int UPC_logo[26][21] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0},
    {0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0},
    {0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0},
    {0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
    {0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0},
    {0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0},
    {0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0},
    {0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0},
    {0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0},
    {0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0},
    {0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int seega_banner[9][24] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0},
    {0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,0},
    {0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0},
    {0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0},
    {0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

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

void drawLogo() {
    int k;
    for (int j = 0; j < 26; j++) {
        k = 0;
        for (int i = 31; i < 21+31; i++) {
            if(UPC_logo[j][k] == 1) {
                Console::ForegroundColor = ConsoleColor::Red;
                Console::SetCursorPosition((i * 2), j);
                cout << char(219) << char(219);
            }
            k++;
        }
    }
}

void drawBanner() {
    int k, l;
    k = 0;
    for (int j = 27; j < 9+27; j++) {
        l = 0;
        for (int i = 29; i < 24+29; i++) {
            if (seega_banner[k][l] == 0) {
                Console::ForegroundColor = ConsoleColor::White;
                Console::SetCursorPosition((i * 2), j);
                cout << char(219) << char(219);
            }
            l++;
        }
        k++;
    }
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(55, 41);
    cout << "Elaborado por Bruce Matias Fleck Ojeda   -   U20211E803";
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::SetCursorPosition(60, 44);
    cout << "Precione cualquier tecla para continuar...";
}

void instructions() {
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(59, 2);
    cout << "------------------ INSTRUCCIONES DEL JUEGO ------------------";
    Console::SetCursorPosition(45, 5);
    cout << "Seega (tambien conocido como siga, sega o sipu) es un juego de mesa de origen";
    Console::SetCursorPosition(45, 6);
    cout << "Epipcio que consiste de dos jugadores con 12 fichas cada uno intentando capturar";
    Console::SetCursorPosition(45, 7);
    cout << "todas las fichas de su oponente. El juego se realiza en un tablero de 5x5";
    Console::SetCursorPosition(45, 9);
    cout << "El juego se divide en dos fases:";
    Console::SetCursorPosition(45, 11);
    cout << "Primera fase.";
    Console::SetCursorPosition(45, 13);
    cout << char(46) << " Los dos jugadores, por turno, van colocando 2 fichas sobre cualquier casilla";
    Console::SetCursorPosition(47, 14);
    cout << "vacia salvo la del centro. La casilla del centro estara vacia hasta la segunda fase del juego.";
    Console::SetCursorPosition(45, 16);
    cout << "Segunda fase.";
    Console::SetCursorPosition(45, 18);
    cout << char(46) << " El jugador que coloca sus 2 últimas fichas es quien comienza la segunda fase.";
    Console::SetCursorPosition(45, 19);
    cout << char(46) << " Alternativamente se va desplazando una ficha a cualquier casilla contigua libre,";
    Console::SetCursorPosition(47, 20);
    cout << "comprendida la del centro, en vertical u horizontal, pero no en diagonal.";
    Console::SetCursorPosition(45, 21);
    cout << char(46) << " Una ficha es capturada y removida si esta es encerrada entre dos fichas contrarias";
    Console::SetCursorPosition(47, 22);
    cout << "(no en sentido diagonal).";
    Console::SetCursorPosition(45, 23);
    cout << char(46) << " Un solo movimiento puede implicar el encierro y la captura de varias piezas a la vez.";
    Console::SetCursorPosition(45, 24);
    cout << char(46) << " El jugador que realiza una captura puede seguir moviendo la misma ficha que realizo";
    Console::SetCursorPosition(47, 25);
    cout << "el ultimo movimiento mientras siga capturando.";
    Console::SetCursorPosition(45, 26);
    cout << char(46) << " Una ficha que se coloca voluntariamente entre dos fichas enemigas no es capturada,";
    Console::SetCursorPosition(47, 27);
    cout << "salvo si una de las piezas enemigas se retira y vuelve.";
    Console::SetCursorPosition(45, 28);
    cout << char(46) << " La ficha que ocupa la casilla central no puede ser capturada.";
    Console::SetCursorPosition(45, 29);
    cout << char(46) << " Cuando un jugador no puede mover le pasa el turno, al contrario.";
    Console::SetCursorPosition(45, 30);
    cout << char(46) << " Se gana si se capturan todas las fichas contrarias.";
    Console::SetCursorPosition(45, 31);
    cout << char(46) << " Cada jugador puede construir una barrera (o muro) con fichas detrás de la cual";
    Console::SetCursorPosition(47, 32);
    cout << "solo se encuentran sus propias fichas que pueden moverse sin peligro de ser capturadas.";
    Console::SetCursorPosition(45, 33);
    cout << char(46) << " En el caso de existir una barrera gana el jugador que tiene la mayor cantidad de fichas,";
    Console::SetCursorPosition(47, 34);
    cout << "si tienen la misma cantidad es un empate.";
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::SetCursorPosition(69, 37);
    cout << "Precione cualquier tecla para continuar...";
}

void drawPlayerInstructions() {
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(38, 2);
    cout << "---------------------------------- INSTRUCCIONES PARA EL JUGADOR -------------------------------------";
    Console::SetCursorPosition(45, 4);
    cout << "Durante el juego podras escojer donde colocar o mover una ficha por medio de un cuadrado selecionador";
    Console::SetCursorPosition(45, 5);
    cout << "de color ";
    Console::ForegroundColor = ConsoleColor::Yellow;
    cout << "amarillo";
    Console::ForegroundColor = ConsoleColor::White;
    cout << " y se mueve usando las teclas de flechas.";
    Console::SetCursorPosition(45, 7);
    cout << "Para colocar una ficha dirije el seleccionador a la casilla que quieras y presiona la tecla [z]";
    Console::SetCursorPosition(45, 8);
    cout << "Para mover una ficha seleccionalo usando la tecla [x], luego dirijete a la casilla donde quieras";
    Console::SetCursorPosition(45, 9);
    cout << "mover la ficha u presiona [x] de nuevo.";
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::SetCursorPosition(69, 12);
    cout << "Precione cualquier tecla para continuar...";
}

void displayAvailableColors(int x, int y) {
    Console::SetCursorPosition(y, x);
    for (int i = 0; i < 5; i++) {
        switch (available_colors[i]) {
        case 'R':
            Console::ForegroundColor = ConsoleColor::White;
            cout << "  [R] = ";
            Console::ForegroundColor = ConsoleColor::Red;
            cout << "Rojo";
            break;
        case 'M':
            Console::ForegroundColor = ConsoleColor::White;
            cout << "  [M] = ";
            Console::ForegroundColor = ConsoleColor::Magenta;
            cout << "Mangenta";
            break;
        case 'B':
            Console::ForegroundColor = ConsoleColor::White;
            cout << "  [B] = ";
            Console::ForegroundColor = ConsoleColor::Blue;
            cout << "Azul";
            break;
        case 'V':
            Console::ForegroundColor = ConsoleColor::White;
            cout << "  [V] = ";
            Console::ForegroundColor = ConsoleColor::Green;
            cout << "Verde";
            break;
        case 'A':
            Console::ForegroundColor = ConsoleColor::White;
            cout << "  [A] = ";
            Console::ForegroundColor = ConsoleColor::Yellow;
            cout << "Amarillo";
            break;
        }
    }
    Console::ForegroundColor = ConsoleColor::White;
}

void player1Input() {
    Console::ForegroundColor = ConsoleColor::Black;
    Console::SetCursorPosition(69, 12);
    cout << "                                                        ";
    Console::CursorVisible = true;
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(45, 12);
    cout << "Jugador 1, por favor ingrese su nombre : ";
    cin >> p1.name;
    Console::SetCursorPosition(45, 14);
    cout << "Hola " << p1.name << "! Ahora porfavor elige un color: ";
    displayAvailableColors(16, 45);
    Console::SetCursorPosition(45, 17);
    cout << "Color: ";
    char color;
    do {
        Console::SetCursorPosition(52, 17);
        cin >> color;
        color = toupper(color);
        if (color != 'R' && color != 'M' && color != 'B' && color != 'A' && color != 'V') {
            Console::SetCursorPosition(52, 17);
            cout << "                   ";
        }
    } while (color != 'R' && color != 'M' && color != 'B' && color != 'A' && color != 'V');
    switch (color) {
    case 'R':
        p1.color = 4;
        break;
    case 'M':
        p1.color = 13;
        break;
    case 'B':
        p1.color = 1;
        break;
    case 'A':
        p1.color = 6;
        break;
    case 'V':
        p1.color = 2;
        break;
    }
    for (int i = 0; i < 5; i++) {
        if (color == available_colors[i]) {
            available_colors[i] = '-';
        }
    }
}

void player2Input() {
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(45, 20);
    cout << "Jugador 2, por favor ingrese su nombre : ";
    cin >> p2.name;
    Console::SetCursorPosition(45, 22);
    cout << "Hola " << p2.name << "! Ahora porfavor elige un color: ";
    displayAvailableColors(24, 45);
    Console::SetCursorPosition(45, 25);
    cout << "Color: ";
    char color;
    bool pass = false;
    do {
        Console::SetCursorPosition(52, 25);
        cout << "                               ";
        Console::SetCursorPosition(52, 25);
        cin >> color;
        color = toupper(color);
        for (int i = 0; i < 5; i++) {
            if (color == available_colors[i]) pass = true;
        }
    } while (!pass);
    switch (color) {
    case 'R':
        p2.color = 4;
        break;
    case 'M':
        p2.color = 13;
        break;
    case 'B':
        p2.color = 1;
        break;
    case 'A':
        p2.color = 6;
        break;
    case 'V':
        p2.color = 2;
        break;
    }
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::SetCursorPosition(69, 30);
    cout << "Precione cualquier tecla para continuar...";
}

void interperate(int num) {
    switch (num) {
    case 0:
        Console::ForegroundColor = ConsoleColor::Cyan; // Light square filling
        cout << char(219) << char(219);
        break;
    case 1:
        Console::ForegroundColor = ConsoleColor::Black; // Dark square filling
        cout << char(219) << char(219);
        break;
    case 9:
        Console::ForegroundColor = ConsoleColor::DarkGray; // Inbetween square filling
        cout << char(219) << char(219);
        break;
    }

}

void printGrid() {
    for (int j = 0; j < TWaH; j++) {
        for (int i = 0; i < TWaH; i++) {
            Console::SetCursorPosition((i * 2), j);
            interperate(grid[j][i]);
        }
        cout << endl;
    }
}

void drawSelector(int x, int y)  { // x = rows, y = columns
    Console::ForegroundColor = ConsoleColor::Yellow;
    int xStartPos = UNIT * (x - 1);
    int yStartPos = UNIT * (y - 1) * 2;
    for (int i = 0; i < (UNIT + 1); i++) {
        // SetCursosPosition parameters are (COLUMNS, ROWS)
        Console::SetCursorPosition(yStartPos + (i * 2), xStartPos); // Top side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos, xStartPos + i); // Left Side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos + (UNIT * 2), xStartPos + i); // Right side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + UNIT);
        cout << char(219) << char(219);
    }
}

void erraseSelector(int x, int y) { // x = rows, y = columns
    Console::ForegroundColor = ConsoleColor::DarkGray;
    int xStartPos = UNIT * (x - 1);
    int yStartPos = UNIT * (y - 1) * 2;
    for (int i = 0; i < (UNIT + 1); i++) {
        // SetCursosPosition parameters are (COLUMNS, ROWS)
        Console::SetCursorPosition(yStartPos + (i * 2), xStartPos); // Top side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos, xStartPos + i); // Left Side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos + (UNIT * 2), xStartPos + i); // Right side
        cout << char(219) << char(219);
        Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + UNIT);
        cout << char(219) << char(219);
    }
}

void placeP1Piece(int x, int y) {
    int xStartPos = UNIT * (x - 1) + 2;
    int yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor(p1.color);
    for (int j = 0; j < 5; j++) {
        for (int i = 1; i <= 5; i++) {
            if ((i == 1 || i == 5) && j == 0) {
            }
            else if ((i == 1 || i == 5) && j == 4) {
            }
            else {
                grid[xStartPos + j][yStartPos + i] = 2;
                Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
                cout << char(219) << char(219);
            }
        }
    }
}

void placeP2Piece(int x, int y) {
    int xStartPos = UNIT * (x - 1) + 2;
    int yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor(p2.color);
    for (int j = 0; j < 5; j++) {
        for (int i = 1; i <= 5; i++) {
            if ((i == 1 || i == 5) && j == 0) {
            }
            else if ((i == 1 || i == 5) && j == 4) {
            }
            else {
                grid[xStartPos + j][yStartPos + i] = 3;
                Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
                cout << char(219) << char(219);
            }
        }
    }
}

void highlight(int x, int y) {
    int xStartPos = UNIT * (x - 1) + 1;
    int yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor::Blue;
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
            cout << char(219) << char(219);
        }
    }
}

void unHighlight(int x, int y) {
    int xStartPos = UNIT * (x - 1) + 1;
    int yStartPos = 2 * UNIT * (y - 1) + 2;
    switch (gridBackground[x - 1][y - 1]) {
    case 0:
        Console::ForegroundColor = ConsoleColor::Cyan;
        break;
    case 1:
        Console::ForegroundColor = ConsoleColor::Black;
        break;
    }
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
            cout << char(219) << char(219);
        }
    }
}

void drawStatsBoard(int p) {
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition((TWaH * 2)+ 5, 0);
    cout << p1.name << " moves: " << p1.moves;
    Console::SetCursorPosition((TWaH * 2) + 5, 1);
    cout << p2.name << " moves: " << p2.moves;
    Console::SetCursorPosition((TWaH * 2) + 5, 3);
    cout << "                                  ";
    Console::SetCursorPosition((TWaH * 2) + 5, 3);
    cout << "It is ";
    switch (p) {
    case 1:
        Console::ForegroundColor = ConsoleColor(p1.color);
        cout << p1.name;
        break;
    case 2:
        Console::ForegroundColor = ConsoleColor(p2.color);
        cout << p2.name;
        break;
    }
    Console::ForegroundColor = ConsoleColor::White;
    cout << "'s turn.";
    for (int i = 0; i < 5; i++) {
        Console::SetCursorPosition((TWaH * 2) + 5 + (i * 4), 5);
        cout << "[" << gridStats[0][i] << "] ";
    }
    for (int i = 0; i < 5; i++) {
        Console::SetCursorPosition((TWaH * 2) + 5 + (i * 4), 6);
        cout << "[" << gridStats[1][i] << "] ";
    }
    for (int i = 0; i < 5; i++) {
        Console::SetCursorPosition((TWaH * 2) + 5 + (i * 4), 7);
        cout << "[" << gridStats[2][i] << "] ";
    }
    for (int i = 0; i < 5; i++) {
        Console::SetCursorPosition((TWaH * 2) + 5 + (i * 4), 8);
        cout << "[" << gridStats[3][i] << "] ";
    }
    for (int i = 0; i < 5; i++) {
        Console::SetCursorPosition((TWaH * 2) + 5 + (i * 4), 9);
        cout << "[" << gridStats[4][i] << "] ";
    }
    Console::SetCursorPosition((TWaH * 2) + 5, 11);
    cout << "                                                                   ";
    Console::SetCursorPosition((TWaH * 2) + 5, 12);
    cout << "                                                                   ";
    Console::SetCursorPosition((TWaH * 2) + 5, 11);
    cout << message1;
    Console::SetCursorPosition((TWaH * 2) + 5, 12);
    cout << message2;
}

void move(int* x, int* y, int p) {
    char key;
    Xant = *x, Yant = *y;
    if (_kbhit) {
        key = toupper(getch());
        switch (key) {
        case 72: // Up arrow
            if (*x - 1 != 0) *x = *x - 1;
            break;
        case 75: // Left arrow
            if (*y - 1 != 0) *y = *y - 1;
            break;
        case 80: // Down arrow
            if (*x - 1 != 4) *x = *x + 1;
            break;
        case 77: // Right arrow
            if (*y - 1 != 4) *y = *y + 1;
            break;
        case 'Z': // Place piece
            if (*x == 3 && *y == 3) {
                message1 = "No puedes colocar una ficha en el cuadro del medio!";
                message2 = "";
            }
            else if (gridStats[*x - 1][*y - 1] == 0) {
                switch (p) {
                case 1:
                    placeP1Piece(*x, *y);
                    p1.moves++;
                    break;
                case 2:
                    placeP2Piece(*x, *y);
                    p2.moves++;
                    break;
                }
                gridStats[*x - 1][*y - 1] = p;
                playerMoved = true;
                message1 = "";
                message2 = "";
            }
            else {
                message1 = "No puedes colocar una ficha encima de otra!";
                message2 = "";
            }
            break;
        case 'X': // Select piece
            if (xHighlight == 0 && yHighlight == 0) {
                if (gridStats[*x - 1][*y - 1] == p) {
                    if (xHighlight != 0 || yHighlight != 0) {
                        unHighlight(xHighlight, yHighlight);
                        switch (p) {
                        case 1:
                            placeP1Piece(xHighlight, yHighlight);
                            break;
                        case 2:
                            placeP2Piece(xHighlight, yHighlight);
                            break;
                        }
                    }
                    xHighlight = *x;
                    yHighlight = *y;
                    highlight(*x, *y);
                    switch (p) {
                    case 1:
                        placeP1Piece(*x, *y);
                        break;
                    case 2:
                        placeP2Piece(*x, *y);
                        break;
                    }
                }
                else if (gridStats[*x - 1][*y - 1] == 0) {
                    message1 = "No se puede seleccionar un cuadro vacio...";
                    message2 = "";
                }
                else {
                    message1 = "No puedes seleccionar la ficha de tu oponente!";
                    message2 = "";
                }
            }
            else { // Moves a piece
                if (xHighlight == *x && yHighlight == *y) {
                    unHighlight(xHighlight, yHighlight);
                    xHighlight = 0;
                    yHighlight = 0;
                    switch (p) {
                    case 1:
                        placeP1Piece(*x, *y);
                        break;
                    case 2:
                        placeP2Piece(*x, *y);
                        break;
                    }
                }
                else if (gridStats[*x - 1][*y - 1] == 0) {
                    if ((abs(*x - xHighlight) == 1 && abs(*y - yHighlight) == 0) || (abs(*x - xHighlight) == 0 && abs(*y - yHighlight) == 1)) {
                        message1 = "";
                        message2 = "";
                        gridStats[*x - 1][*y - 1] = p;
                        gridStats[xHighlight - 1][yHighlight - 1] = 0;
                        switch (p) {
                        case 1:
                            placeP1Piece(*x, *y);
                            break;
                        case 2:
                            placeP2Piece(*x, *y);
                            break;
                        }
                        unHighlight(xHighlight, yHighlight);
                        playerMoved = true;
                        xHighlight = 0;
                        yHighlight = 0;
                    }
                    else {
                        message1 = "Solo puedes colocar una ficha en un cuadro que este directamente";
                        message2 = "arriba, abajo o a los costados de tu ficha seleccionada.";
                    }
                }
                else {
                    if (gridStats[*x - 1][*y - 1] == p) {
                        if (gridStats[*x - 1][*y - 1] == p) {
                            if (xHighlight != 0 || yHighlight != 0) {
                                unHighlight(xHighlight, yHighlight);
                                switch (p) {
                                case 1:
                                    placeP1Piece(xHighlight, yHighlight);
                                    break;
                                case 2:
                                    placeP2Piece(xHighlight, yHighlight);
                                    break;
                                }
                            }
                            xHighlight = *x;
                            yHighlight = *y;
                            highlight(*x, *y);
                            switch (p) {
                            case 1:
                                placeP1Piece(*x, *y);
                                break;
                            case 2:
                                placeP2Piece(*x, *y);
                                break;
                            }
                        }
                    }
                    else {
                        message1 = "No puedes colocar una ficha encima de otra!";
                        message2 = "";
                    }
                }
                break;
            }
            break;
        }
    }
}

int main() {
    Console::CursorVisible = false;
    Console::SetWindowSize(175, 50);

    int x = 3, y = 3;
    int playerTurn = 1;

    // PRE-GAME
        // Intro screen
    drawLogo();
    drawBanner();
    getch();
    Console::Clear();
        // Game instructions
    instructions();
    getch();
    Console::Clear();
        // Player instructions
    drawPlayerInstructions();
    getch();
        // Player name input
    player1Input();
    player2Input();
    Console::CursorVisible = false;
    getch();
    Console::Clear();

    // GAME
    printGrid();
    placeP1Piece(1, 3);
    gridStats[0][2] = 1;
    placeP1Piece(5, 3);
    gridStats[4][2] = 1;
    placeP2Piece(3, 1);
    gridStats[2][0] = 2;
    placeP2Piece(3, 5);
    gridStats[2][4] = 2;
    while (true) {

        // Game updates
        playerMoved = false;

        drawStatsBoard(playerTurn);
        drawSelector(x, y);
        move(&x, &y, playerTurn);
        erraseSelector(Xant, Yant);

        if (playerMoved) {
            switch (playerTurn) {
            case 1:
                playerTurn = 2;
                break;
            case 2:
                playerTurn = 1;
                break;
            }
        }
    }

    // POST-GAME
    getch();
}
