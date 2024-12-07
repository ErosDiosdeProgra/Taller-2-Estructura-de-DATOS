#include "Tablero.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

Tablero :: Tablero(){               // esto era para elegir al azar el jugador, creo que escuche al profe decir eso
    for(int i = 0; i < 3; i++){   //supongo que tmb se debe aplicar al minimax ???
        for(int j = 0; j < 3; j++){ 
            tablero[i][j] = '_';
        }
    }

    srand(static_cast<unsigned>(time(0)));
    turnoJugador = rand() % 2 == 0;
}

void Tablero :: mostrarTablero() const{
    cout << "Reglas del juego - las posiciones van del 1 al 9 de izquierda a derecha para elegir donde marcar: " << endl;
    cout << "1 | 2 | 3 " << endl;
    cout << "_ | _ | _ " << endl;
    cout << "4 | 5 | 6 " << endl;
    cout << "_ | _ | _ " << endl;
    cout << "7 | 8 | 9 " << endl;
    cout << "  |   |   " << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero[i][j];
            if (j < 2) cout << " |";
        }
        if (i < 2) cout << "\n---+---+---\n";
    }
    cout << "\n";
}

bool Tablero :: marcarPosicion(int posicion) {
    if (posicion < 1 || posicion > 9) return false; // Posición inválida

    // Convertir posición (1-9) a coordenadas de la matriz (ya que desde el punto de vista del usuario, seria mas intuitivo que por fila y columna)
    // el -1 tomando que 0 es el inicio
    int fila = (posicion - 1) / 3;
    int columna = (posicion - 1) % 3;

    if (tablero[fila][columna] != '_') return false; // Espacio ocupado

    // Marcar la casilla con el símbolo del jugador actual
    tablero[fila][columna] = turnoJugador ? 'X' : 'O';  //esto para que se entienda es para el bool, sigue el siguiente formato: condicion? (true) : (false)
    return true;
}

char Tablero :: hayGanador() const {
    // Validación horizontal
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] != '_' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0];
        }
    }
    // Validación vertical
    for (int i = 0; i < 3; i++) {
        if (tablero[0][i] != '_' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) {
            return tablero[0][i];
        }
    }
    // Validación diagonal (izquierda a derecha)
    if (tablero[0][0] != '_' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    // Validación diagonal (derecha a izquierda)
    if (tablero[0][2] != '_' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }
    return '_'; // No hay ganador aún
}

bool Tablero :: hayEmpate() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == '_') return false; // Hay espacios vacíos, por lo que continua, sino es true, por lo tanto empate
        }
    }
    return true; 
}

void Tablero :: cambiarTurno() {
    turnoJugador = !turnoJugador;
}

char Tablero :: jugadorActual() const {
    return turnoJugador ? 'X' : 'O';   //esto para que se entienda es para el bool, sigue el siguiente formato: condicion? (si es true, toma este valor) : (false, toma este)
}                                      //es una forma resumida en vez de hacer varios if

Tablero :: ~Tablero(){
}