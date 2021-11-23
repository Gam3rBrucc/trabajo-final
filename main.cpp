#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
using namespace System;

const short UNIT = 8; // Size of a square
const short TWaH = (5 * UNIT) + 1; // Board Width and Height
short Xant = 3, Yant = 3; // X anterior, Y anterior
short xHighlight = 0, yHighlight = 0;
short piecesPlaced = 0;
bool playerMoved;
bool secondFase = false;
bool capture = false;
bool winner = false;
short playerWhoWon;

struct player {
    string name;
    short color;
    short captured_pieces = 0;
    short moves = 0;
    short piecesPlaced = 0;
};

player p1;
player p2;

string message1;
string message2;
string playerTurnMsg;

char available_colors[5] = {'A','B','V','M','R'};

short UPC_logo[26][21] = {
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

short seega_banner[9][24] = {
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

short grid[TWaH][TWaH] = {
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
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,5,1,1,1,1,1,5,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,5,1,1,1,5,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,5,1,5,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,5,1,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,1,5,1,5,1,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,1,5,1,1,1,5,1,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
    {9,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,9,5,1,1,1,1,1,5,9,0,0,0,0,0,0,0,9,1,1,1,1,1,1,1,9},
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

short gridStats[5][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};

short gridBackground[5][5] = {
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,5,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1}
};

void drawLogo() {
    short k;
    for (short j = 0; j < 26; j++) {
        k = 0;
        for (short i = 31; i < 21+31; i++) {
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
    short k, l;
    k = 0;
    for (short j = 27; j < 9+27; j++) {
        l = 0;
        for (short i = 29; i < 24+29; i++) {
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
    cout << char(46) << " Cada jugador puede construir una barrera (o muro) con fichas detras de la cual";
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
    cout << "mover la ficha u presiona [x] de nuevo. Para pasar tu turno y darle turno a tu oponente";
    Console::SetCursorPosition(45, 10);
    cout << "presiona [t]. Para parar el juego preciona [q] y el jugador con mas capturas ganara.";
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::SetCursorPosition(69, 12);
    cout << "Precione cualquier tecla para continuar...";
}

void displayAvailableColors(short x, short y) {
    Console::SetCursorPosition(y, x);
    for (short i = 0; i < 5; i++) {
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
    for (short i = 0; i < 5; i++) {
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
        for (short i = 0; i < 5; i++) {
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

void interperate(short num) {
    switch (num) {
    case 0:
        Console::ForegroundColor = ConsoleColor::Cyan; // Light square filling
        cout << char(219) << char(219);
        break;
    case 1:
        Console::ForegroundColor = ConsoleColor::Black; // Dark square filling
        cout << char(219) << char(219);
        break;
    case 5:
        Console::ForegroundColor = ConsoleColor::DarkCyan;
        cout << char(219) << char(219);
        break;
    case 9:
        Console::ForegroundColor = ConsoleColor::DarkGray; // Inbetween square filling
        cout << char(219) << char(219);
        break;
    }

}

void printGrid() {
    for (short j = 0; j < TWaH; j++) {
        for (short i = 0; i < TWaH; i++) {
            Console::SetCursorPosition((i * 2), j);
            interperate(grid[j][i]);
        }
        cout << endl;
    }
}

void drawSelector(short x, short y)  { // x = rows, y = columns
    Console::ForegroundColor = ConsoleColor::Yellow;
    short xStartPos = UNIT * (x - 1);
    short yStartPos = UNIT * (y - 1) * 2;
    for (short i = 0; i < (UNIT + 1); i++) {
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

void erraseSelector(short x, short y) { // x = rows, y = columns
    Console::ForegroundColor = ConsoleColor::DarkGray;
    short xStartPos = UNIT * (x - 1);
    short yStartPos = UNIT * (y - 1) * 2;
    for (short i = 0; i < (UNIT + 1); i++) {
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

void placeP1Piece(short x, short y) {
    short xStartPos = UNIT * (x - 1) + 2;
    short yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor(p1.color);
    for (short j = 0; j < 5; j++) {
        for (short i = 1; i <= 5; i++) {
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

void placeP2Piece(short x, short y) {
    short xStartPos = UNIT * (x - 1) + 2;
    short yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor(p2.color);
    for (short j = 0; j < 5; j++) {
        for (short i = 1; i <= 5; i++) {
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

void highlight(short x, short y) {
    short xStartPos = UNIT * (x - 1) + 1;
    short yStartPos = 2 * UNIT * (y - 1) + 2;
    Console::ForegroundColor = ConsoleColor::Blue;
    for (short j = 0; j < 7; j++) {
        for (short i = 0; i < 7; i++) {
            Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
            cout << char(219) << char(219);
        }
    }
}

void unHighlight(short x, short y) {
    short xStartPos = UNIT * (x - 1) + 1;
    short yStartPos = 2 * UNIT * (y - 1) + 2;
    short bruh[7][7] = {
        {5,1,1,1,1,1,5},
        {1,5,1,1,1,5,1},
        {1,1,5,1,5,1,1},
        {1,1,1,5,1,1,1},
        {1,1,5,1,5,1,1},
        {1,5,1,1,1,5,1},
        {5,1,1,1,1,1,5}
    };
    switch (gridBackground[x - 1][y - 1]) {
    case 0:
        Console::ForegroundColor = ConsoleColor::Cyan;
        break;
    case 1:
        Console::ForegroundColor = ConsoleColor::Black;
        break;
    }
    if (gridBackground[x - 1][y - 1] == 5) {
        for (short i = 17; i < 24; i++) {
            for (short j = 17; j < 24; j++) {
                Console::SetCursorPosition((j * 2), i);
                cout << "  ";
            }
        }
        short k = 0;
        for (short i = 17; i < 24; i++) {
            short q = 0;
            for (short j = 17; j < 24; j++) {
                Console::SetCursorPosition((j * 2), i);
                interperate(bruh[k][q]);
                ++q;
            }
            ++k;
        }
    }
    else {
        for (short j = 0; j < 7; j++) {
            for (short i = 0; i < 7; i++) {
                Console::SetCursorPosition(yStartPos + (i * 2), xStartPos + j);
                cout << char(219) << char(219);
            }
        }
    }
}

void drawStatsBoard(short p) {
    Console::BackgroundColor = ConsoleColor::Black;
    Console::SetCursorPosition((TWaH * 2) + 5, 3);
    cout << "                                  ";
    Console::ForegroundColor = ConsoleColor::Black;
    switch (p) {
    case 1:
        Console::BackgroundColor = ConsoleColor(p1.color);
        break;
    case 2:
        Console::BackgroundColor = ConsoleColor(p2.color);
        break;
    }
    Console::SetCursorPosition((TWaH * 2) + 5, 3);
    cout << "Le toca a ";
    switch (p) {
    case 1:
        cout << p1.name;
        break;
    case 2:
        cout << p2.name;
        break;
    }
    Console::BackgroundColor = ConsoleColor::Black;
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition((TWaH * 2) + 5, 5);
    cout << p1.name << " movimientos: " << p1.moves;
    Console::SetCursorPosition((TWaH * 2) + 5, 6);
    cout << p2.name << " movimientos: " << p2.moves;
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition((TWaH * 2) + 5, 8);
    cout << "Fichas capturadas por ";
    Console::ForegroundColor = ConsoleColor(p1.color);
    cout << p1.name;
    Console::ForegroundColor = ConsoleColor::White;
    cout << ": " << p1.captured_pieces;
    Console::SetCursorPosition((TWaH * 2) + 5, 9);
    cout << "Fichas capturadas por ";
    Console::ForegroundColor = ConsoleColor(p2.color);
    cout << p2.name;
    Console::ForegroundColor = ConsoleColor::White;
    cout << ": " << p2.captured_pieces;
    Console::SetCursorPosition((TWaH * 2) + 5, 11);
    cout << "                                                                                        ";
    Console::SetCursorPosition((TWaH * 2) + 5, 12);
    cout << "                                                                                        ";
    Console::ForegroundColor = ConsoleColor::Black;
    Console::BackgroundColor = ConsoleColor::White;
    Console::SetCursorPosition((TWaH * 2) + 5, 11);
    cout << message1;
    Console::SetCursorPosition((TWaH * 2) + 5, 12);
    cout << message2;
    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Black;
}

void checkForPieceCapture(short x, short y, short p) {
    --x;
    --y;
    short upperX = x - 2;
    short lowerX = x + 2;
    short leftY = y - 2;
    short rightY = y + 2;
    short opponent;
    switch (p) {
    case 1:
        opponent = 2;
        break;
    case 2:
        opponent = 1;
        break;
    }
    if (upperX >= 0) { // Checks if piece above can be captured
        if (gridStats[upperX][y] == p && gridStats[x - 1][y] == opponent) {
            unHighlight(x, y + 1);
            gridStats[x - 1][y] = 0;
            capture = true;
            switch (p) {
            case 1:
                ++p1.captured_pieces;
                break;
            case 2:
                ++p2.captured_pieces;
                break;
            }
        }
    }
    if (lowerX <= 4) { // Checks if piece below can be captured
        if (gridStats[lowerX][y] == p && gridStats[x + 1][y] == opponent) {
            unHighlight(x + 2, y + 1);
            gridStats[x + 1][y] = 0;
            capture = true;
            switch (p) {
            case 1:
                ++p1.captured_pieces;
                break;
            case 2:
                ++p2.captured_pieces;
                break;
            }
        }
    }
    if (leftY >= 0) { // Checks if piece to the left can be captured
        if (gridStats[x][leftY] == p && gridStats[x][y - 1] == opponent) {
            unHighlight(x + 1, y);
            gridStats[x][y - 1] = 0;
            capture = true;
            switch (p) {
            case 1:
                ++p1.captured_pieces;
                break;
            case 2:
                ++p2.captured_pieces;
                break;
            }
        }
    }
    if (rightY <= 4) { // Checks if piece to the right can be captured
        if (gridStats[x][rightY] == p && gridStats[x][y + 1] == opponent) {
            unHighlight(x + 1, y + 2);
            gridStats[x][y + 1] = 0;
            capture = true;
            switch (p) {
            case 1:
                ++p1.captured_pieces;
                break;
            case 2:
                ++p2.captured_pieces;
                break;
            }
        }
    }
}

bool checkLocalAvailableCaptures(short x, short y, short p) {
    bool capture_available = false;
    short upperX = x - 2;
    short lowerX = x + 2;
    short leftY = y - 2;
    short rightY = y + 2;
    short opponent;
    switch (p) {
    case 1:
        opponent = 2;
        break;
    case 2:
        opponent = 1;
        break;
    }
    if (upperX >= 0) {
        if (((x-1) != 2 || y != 2) && gridStats[upperX][y] == p && gridStats[x - 1][y] == opponent) capture_available = true;
    }
    if (lowerX <= 4) {
        if (((x + 1) != 2 || y != 2) && gridStats[lowerX][y] == p && gridStats[x + 1][y] == opponent) capture_available = true;
    }
    if (leftY >= 0) {
        if ((x != 2 || (y-1) != 2) && gridStats[x][leftY] == p && gridStats[x][y - 1] == opponent) capture_available = true;
    }
    if (rightY <= 4) {
        if ((x != 2 || (y + 1) != 2) && gridStats[x][rightY] == p && gridStats[x][y + 1] == opponent) capture_available = true;
    }
    return capture_available;
}

bool checkAvailableCaptures(short x, short y, short p) {
    bool capture_available = false;
    bool a = false, b = false, c = false, d = false;
    --x;
    --y;
    if (gridStats[x - 1][y] == 0) {
        a = checkLocalAvailableCaptures(x - 1, y, p);
    }
    if (gridStats[x + 1][y] == 0) {
        b = checkLocalAvailableCaptures(x + 1, y, p);
    }
    if (gridStats[x][y - 1] == 0) {
        c = checkLocalAvailableCaptures(x, y - 1, p);
    }
    if (gridStats[x][y + 1] == 0) {
        d = checkLocalAvailableCaptures(x, y + 1, p);
    }
    if (a || b || c || d) {
        capture_available = true;
    }
    return capture_available;
}

void move(short* x, short* y, short p) {
    char key;
    Xant = *x, Yant = *y;
    // Changes x and y coordinates depending on player input
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
            if (secondFase) {
                message1 = "Ya no puedes colocar fichas!";
                message2 = "";
            }
            else {
                if (*x == 3 && *y == 3) {
                    message1 = "No puedes colocar una ficha en el cuadro del medio!";
                    message2 = "";
                }
                else if (gridStats[*x - 1][*y - 1] == 0) { // Checks if square is empty
                    switch (p) {
                    case 1:
                        placeP1Piece(*x, *y);
                        ++p1.moves;
                        ++p1.piecesPlaced;
                        break;
                    case 2:
                        placeP2Piece(*x, *y);
                        ++p2.moves;
                        ++p2.piecesPlaced;
                        break;
                    }
                    gridStats[*x - 1][*y - 1] = p;
                    ++piecesPlaced;
                    if (piecesPlaced == 2) { // Allows each player to place two pieces at a time
                        playerMoved = true;
                        piecesPlaced = 0;
                    }
                    message1 = "";
                    message2 = "";
                }
                else {
                    message1 = "No puedes colocar una ficha encima de otra!";
                    message2 = "";
                }
            }
            break;
        case 'X': // Select piece
            if (secondFase) {
                if (xHighlight == 0 && yHighlight == 0) { // Checks if there are any sqaures highlighted
                    if (gridStats[*x - 1][*y - 1] == p) {
                        // Checks if the square the player wants to highlight has that players piece in it
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
                else {
                    if (xHighlight == *x && yHighlight == *y) { // Unselects a piece
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
                        message1 = "";
                        message2 = "";
                    }
                    else if (gridStats[*x - 1][*y - 1] == 0) { // Moves a piece
                        if ((abs(*x - xHighlight) == 1 && abs(*y - yHighlight) == 0) || (abs(*x - xHighlight) == 0 && abs(*y - yHighlight) == 1)) {
                            message1 = "";
                            message2 = "";
                            gridStats[*x - 1][*y - 1] = p;
                            gridStats[xHighlight - 1][yHighlight - 1] = 0;
                            switch (p) {
                            case 1:
                                ++p1.moves;
                                placeP1Piece(*x, *y);
                                checkForPieceCapture(*x, *y, p);
                                break;
                            case 2:
                                ++p2.moves;
                                placeP2Piece(*x, *y);
                                checkForPieceCapture(*x, *y, p);
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
                    else { // Selects another piece
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
                            message1 = "";
                            message2 = "";
                        }
                        else {
                            message1 = "No puedes colocar una ficha encima de otra!";
                            message2 = "";
                        }
                    }
                }
            }
            else {
                message1 = "Aun no puedes seleccionar fichas, termina de colocarlas primero!";
                message2 = "";
            }
            break;
        case 'T':
            playerMoved = true;
            break;
        case 'Q':
            winner = true;
            break;
        }
    }
}

void checkForWinner() {
    if (p1.captured_pieces == 12) {
        winner = true;
        playerWhoWon = 1;
    }
    else if (p2.captured_pieces == 12) {
        winner = true;
        playerWhoWon = 2;
    }
}

int main() {
    Console::CursorVisible = false;
    Console::SetWindowSize(175, 50);

    short x = 3, y = 3;
    short playerTurn = 1;

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

    while (!winner) {

        playerMoved = false;
        capture = false;

        drawStatsBoard(playerTurn);
        drawSelector(x, y);
        move(&x, &y, playerTurn);
        erraseSelector(Xant, Yant);

        if (capture && checkAvailableCaptures(x, y, playerTurn)) {
            playerMoved = false;
            message1 = "Como has realizado una captura y tienes posibilidad puedes mover de nuevo.";
            message2 = "Quisieras mover de nuevo o pasar tu turno a tu oponente?";
        }

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

        if (p1.piecesPlaced >= 10 && p2.piecesPlaced >= 10 && secondFase == false) {
            secondFase = true;
            playerTurn = 2;
        }

        checkForWinner();
    }

    // POST-GAME
    if (p1.captured_pieces > p2.captured_pieces) {
        playerWhoWon = 1;
    }
    else if (p1.captured_pieces < p2.captured_pieces) {
        playerWhoWon = 2;
    }

    Console::ForegroundColor = ConsoleColor::Black;
    for (short i = 0; i < 175; i++) {
        for (short j = 0; j < 21; j++) {
            Console::SetCursorPosition(i,j+15);
            cout << char(219);
        }
    }
    switch (playerWhoWon) {
    case 1:
        Console::ForegroundColor = ConsoleColor(p1.color);
        break;
    case 2:
        Console::ForegroundColor = ConsoleColor(p2.color);
        break;
    }
    for (short i = 58; i < 116; i++) {
        Console::SetCursorPosition(i, 22);
        cout << char(219);
    }
    for (short i = 58; i < 116; i++) {
        Console::SetCursorPosition(i, 28);
        cout << char(219);
    }
    for (short i = 22; i < 28; i++) {
        Console::SetCursorPosition(58, i);
        cout << char(219);
        Console::SetCursorPosition(115, i);
        cout << char(219);
    }
    Console::SetCursorPosition(75, 25);
    switch (playerWhoWon) {
    case 1:
        cout << p1.name << " GANO!!!!!!!!!!!!!!!";
        break;
    case 2:
        cout << p2.name << " GANO!!!!!!!!!!!!!!!";
        break;
    }
    getch();
}
