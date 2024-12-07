#include <iostream>
#include "Tablero.h"
using namespace std;

void jugar() {
    Tablero tablero;
    int posicion;

    cout << "¡Bienvenido al juego del GATO!"<< endl;
    tablero.mostrarTablero();

    while (true) {
        cout << "Turno del jugador " << tablero.jugadorActual() << ". Ingresa una posición (1-9): ";
        cin >> posicion;

        if (!tablero.marcarPosicion(posicion)) {
            cout << "Movimiento no válido. Intenta de nuevo." << endl;
            continue;
        }

        tablero.mostrarTablero();

        char ganador = tablero.hayGanador();
        if (ganador != '_') {
            cout << "¡El jugador " << ganador << " ha ganado!"<< endl;
            break;
        }

        if (tablero.hayEmpate()) {
            cout << "¡Es un empate!"<< endl;
            break;
        }

        tablero.cambiarTurno();
    }
}

int main() {   //hay que hacer el menu (eleccion de 2 jugadores, y la version jugador contra maquina), ya esta hecha la version 2 jugadores
    jugar();
    return 0;
}