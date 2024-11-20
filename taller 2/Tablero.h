#pragma once
#include <iostream>           //esto despues lo voy a arreglar y lo dejare mas ordenado y coherente con el juego
using namespace std;

class Tablero {
    private:
        char tablero[3][3];
      //tecnicamente es por el jugador "X" o "O"

    public: 
        Tablero();                 //estas funciones NO están aplicadas, pero estan puestas para despues aplicarlas en el tablero.cpp
        void mostrarTablero();
        void turnoJugador(); //este será para hacer lo del azar (no esta hecho)
        void cambiarJugador();
        bool marcarTablero(int fila, int columna); //quiero que seleccione del 1 al 9 por posicion
        bool ganador();
        bool empate();
        ~Tablero();
};

/** lo quiero modificar para que el jugador no este escribiendo fila y columna, sino que elija por posicion (1 al 9):
 *        1 | 2 | 3 
 *        --|---|--
 *        4 | 5 | 6
 *        --|---|--
 *        7 | 8 | 9
 *  
 * asi es como lo pondre despues para que elija el jugador (se pondra en las reglas, encuentro que es mas sencillo desde el
 * punto de vista del jugador)
 * pero de momento esta con fila y columna que tiene que escribir el Comparitox 
 */