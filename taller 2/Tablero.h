#pragma once
#include <iostream>

class Tablero {
    private:
        char tablero[3][3];
        bool  turnoJugador;   //para ver si es "X" o "O"

    public:
        Tablero();
        void mostrarTablero() const;
        bool marcarPosicion(int posicion);
        char hayGanador() const;
        bool hayEmpate() const;
        void cambiarTurno();
        char jugadorActual() const;
        ~Tablero();
};