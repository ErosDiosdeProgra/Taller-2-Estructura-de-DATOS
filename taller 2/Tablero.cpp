#include "Tablero.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/*Aqui en el constructor se rellena el tablero y de decide aleatoriamente 
cual de los jugadores comienza la partida*/
Tablero :: Tablero(){               
    for(int i = 0; i < 3; i++){   
        for(int j = 0; j < 3; j++){ 
            tablero[i][j] = '_';
        }
    }

    srand(static_cast<unsigned>(time(0)));   // esto era para elegir al azar el jugador, creo que escuche al profe decir eso
    turnoJugador = rand() % 2 == 0;          //supongo que tmb se debe aplicar al minimax ???
}

/*esta funcion imprime por pantalla las reglas del juego (posiciones elegibles) y tambien va mostrando
por turno como va cambiando el tablero cada que se llama a esta funcion*/
void Tablero :: mostrarTablero() const{
    cout << "Reglas del juego - las posiciones van del 1 al 9 de izquierda a derecha para elegir donde marcar: " << endl;
    cout << " " << endl;
    cout << "1 | 2 | 3 " << endl;
    cout << "_ | _ | _ " << endl;
    cout << "4 | 5 | 6 " << endl;
    cout << "_ | _ | _ " << endl;
    cout << "7 | 8 | 9 " << endl;
    cout << "  |   |   " << endl;
    cout << "          " << endl;
    cout << "          " << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero[i][j];
            if (j < 2) cout << " |";
        }
        if (i < 2) cout << "\n---|---|---\n";
    }
    cout << "\n";
    cout << " " << endl;
}

/*En esta funcion se hace un cambio de posicion (1 al 9) a coordenadas de matriz para marcar la posicion
correspondiente. En caso de estar ocupado la posicion retorna falso (no se podra marcar) y si no esta ocupado
entonces marca la posicion seleccionada*/
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

/*Esta funcion verifica por filas, columnas y diagonales si es que existe un ganador (ya sea jugador X o jugador O)
si no hay ganador retorna "_" lo que significa que debe seguir el juego ejecutandose*/
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

/*Esta funcion va a comprobar si es que existe un empate en la partida (ningun jugador gana) para eso va a 
recorrer la matriz y verificar si esta completada, ya que si retorna '_' significa que aun no
se acaba la partida por lo que no puede haber empate*/
bool Tablero :: hayEmpate() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == '_') return false; // Hay espacios vacíos, por lo que continua, sino es true, por lo tanto empate
        }
    }
    return true; 
}

/*Esta funcion es para que luego de finalizado un turno, se cambie al otro jugador (ya que se van intercambiando)*/
void Tablero :: cambiarTurno() {
    turnoJugador = !turnoJugador;
}

/*Esta funcion retorna al jugador actual en aquel turno, el cual es utilizado luego en otras funciones*/
char Tablero :: jugadorActual() const {
    return turnoJugador ? 'X' : 'O';   //esto para que se entienda es para el bool, sigue el siguiente formato: condicion? (si es true, toma este valor) : (false, toma este)
}                                      //es una forma resumida en vez de hacer varios if

/*Este es el destructor del objeto tablero*/
Tablero :: ~Tablero(){
}

/*En esta funcion se evalua a la IA, donde dependiendo del retorno, se señala que gana o pierde la IA*/
int Tablero::evaluar() const {
    char ganador = hayGanador();
    if (ganador == 'X') return -10; // IA pierde
    if (ganador == 'O') return 10;  // IA gana
    return 0; // Empate o no hay ganador
}

/*En esta funcion se aplica el algoritmo minimax junto con la poda*/
int Tablero::minimax(bool esMaximizador, int alpha, int beta) {
    int puntaje = evaluar();  // Evaluamos el estado actual del tablero                                      
    if (puntaje == 10 || puntaje == -10) {
        return puntaje; // Si hay un ganador, devolvemos el puntaje
    }
    if (hayEmpate()) {
        return 0;  // Si es empate, devolvemos 0
    }

    if (esMaximizador) {     //IA jugando (circulo)
        int mejor = -1000;
        // Recorrer todo el tablero
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] == '_') {
                    tablero[i][j] = 'O'; // IA juega
                    int valor = minimax(false, alpha, beta);  // Llamada recursiva para el jugador
                    tablero[i][j] = '_'; // Deshacer movimiento
                    mejor = max(mejor, valor);  // Maximizar el puntaje
                    alpha = max(alpha, mejor);  // Actualizar alpha
                    if (beta <= alpha) {
                        break; // Si la poda se activa, salimos del bucle
                    }
                }
            }
        }
        return mejor;
    } else {
        int mejor = 1000;
        // Recorrer todo el tablero
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] == '_') {
                    tablero[i][j] = 'X'; // El jugador juega
                    int valor = minimax(true, alpha, beta);  // Llamada recursiva para la IA
                    tablero[i][j] = '_'; // Deshacer movimiento
                    mejor = min(mejor, valor);  // Minimizar el puntaje
                    beta = min(beta, mejor);  // Actualizar beta
                    if (beta <= alpha) {
                        break; // Si la poda se activa, salimos del bucle
                    }
                }
            }
        }
        return mejor;
    }
}

/*Esta funcion es donde la IA va a decidir cual es el mejor movimiento para elegir, y luego 
de analizarlo, retorna el mejor movimiento que el cree*/
int Tablero::mejorMovimiento() {
    int mejorValor = -1000;
    int mejorMovimiento = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == '_') {
                tablero[i][j] = 'O'; // IA juega
                if (hayGanador() == 'O') {
                    tablero[i][j] = '_'; // Deshacer movimiento
                    return i * 3 + j + 1; // Convertir coordenadas a posición 1-9
                }
                tablero[i][j] = '_'; // Deshacer movimiento
            }
        }
    }

    for(int i = 0; i<3; i++) {
        for(int j = 0; j<3; j++) {
            if (tablero[i][j] == '_') {
                tablero[i][j] = 'X'; // Probar si el jugador 1 (X) puede ganar aquí
                if (hayGanador() == 'X') {
                    tablero[i][j] = 'O'; // Bloquear al jugador 1 (X)
                    return i * 3 + j + 1; // Convertir coordenadas a posición 1-9
                }
                tablero[i][j] = '_'; // Deshacer movimiento
            }
        }
    }
    // Recorrer todo el tablero
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == '_') {
                tablero[i][j] = 'O'; // La IA juega
                int valorMovimiento = minimax(true, -1000, 1000);  // Llamada a minimax con poda alfa-beta
                tablero[i][j] = '_'; // Deshacer movimiento

                if (valorMovimiento > mejorValor) {
                    mejorValor = valorMovimiento;
                    mejorMovimiento = i * 3 + j + 1; // Convertir coordenadas a posición 1-9
                }
            }
        }
    }
    return mejorMovimiento;
}

