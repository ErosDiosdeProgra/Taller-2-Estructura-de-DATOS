#include <iostream>
#include <limits>
#include <stdexcept>
#include "Tablero.h"
using namespace std;

/**Esta funcion activa lo que seria el modo de 2 jugadores reales
y además elige al azar cual de los 2 jugadores ("X" o "O" empieza) */
void jugar() {
    Tablero tablero;
    int posicion;
    
    cout << " " << endl;
    cout << "Elegiste la opcion de Jugador1 (X) v/s Jugador2 (O)"<< endl;
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
            cout << " " << endl;
            cout << "¡El jugador " << ganador << " ha ganado!"<< endl;
            cout << " " << endl;
            break;
        }

        if (tablero.hayEmpate()) {
            cout << "¡Es un empate!"<< endl;
            break;
        }

        tablero.cambiarTurno();
    }
}

/*Esta funcion muestra el menu sobre el cual funciona el juego, aqui el jugador(es) puede
seleccionar el modo de juego*/
int mostrarMenu(){
    cout<<  "******Bienvenido al MENU principal del GATO******" << endl;
    cout<<  "Seleccione una de las siguientes opciones: " << endl;
    cout<<  "1) Jugador contra Jugador" << endl;
    cout<<  "2) Jugador contra maquina" << endl;
    cout<<  "3) Salir del juego" << endl;
    int op;
    cout << "> ";
    cin >> op;

    if (cin.fail()) {
        cin.clear(); // Entre el fail y el clear, se encargan de ver si falla la entrada (por pedir un int y que nos den otro tipo) y el clear "limpia" cin pa que no hayan errores
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //se ignoran la mayor cantidad de numeros que se encuentren hasta un salto de linea (el enter u espacio)
        throw invalid_argument("Entrada invalida, ingrese un numero");
    }
    return op;
}

/*En esta funcion se ejecuta la version de jugador contra maquina, aqui la maquina
utiliza el algoritmo minimax para poder vencer al jugador*/
void jugarContraMaquina(){
    Tablero tablero;  // Declarado dentro del bloque
        int posicion;

        cout << " " << endl;
        cout << "Seleccionaste jugar contra la maquina" << endl;

        while (true) {
            tablero.mostrarTablero();

            if (tablero.jugadorActual() == 'X') {
                cout << "Turno del jugador. Ingresa una posición (1-9): ";
                cin >> posicion;
                if (!tablero.marcarPosicion(posicion)) {
                    cout << "Movimiento no válido. Intenta de nuevo." << endl;
                    continue;
                }
            }

            if (tablero.jugadorActual() == 'O') {
                cout << "Turno de la máquina..." << endl;
                posicion = tablero.mejorMovimiento();
                tablero.marcarPosicion(posicion);
                cout << "La máquina marcó la posición " << posicion << "." << endl;
            }

            tablero.cambiarTurno();

            // Verificar si hay ganador o empate después de cada movimiento
            char ganador = tablero.hayGanador();
            if (ganador != '_') {  // Si hay un ganador
                tablero.mostrarTablero();
                cout << "¡El jugador " << ganador << " ha ganado!" << endl;
                break;
            }

            if (tablero.hayEmpate()) {  // Si hay empate
                tablero.mostrarTablero();
                cout << "¡Es un empate!" << endl;
                break;
            }
        }
}

int main() {
    bool menu = true;
    while(menu){
        int opcion = mostrarMenu();
        switch (opcion){
        case 1:
            jugar();
            break;

        case 2: 
            jugarContraMaquina();
            break;

        case 3:
            cout << " " << endl;
            cout << "Seleccionaste salir del sistema" << endl;
            cout << "Saliendo ...." << endl;
            menu = false;
            break;

        default:
            cout << "Seleccion invalida. Por favor ingrese de nuevo una opcion" << endl;
            break;
        }
    }

    return 0;
}
