#include <iostream>
#include "Tablero.h"
#include <limits>
#include <stdexcept>
using namespace std;

/**ESTO ES MOMENTANEO, SI SE COMPLICA LO PODEMOS SIMPLIFICAR PERO COMO PIDE QUE SE PRUEBE ENTRE 2 JUGADORES Y LUEGO
 * QUE LO PROBEMOS CON LA I.A ENTONCES POR ESO LO HICE ASÍ.*/

int mostrarOpciones(){
    cout << "1. Singleplayer (Jugador v/s I.A)" << endl;
    cout << "2. Multiplayer (Jugador1 v/s Jugador2)" << endl;
    cout << "3. Descargar mas RAM" << endl;
    cout << "0. Salir del juego" << endl;
    cout << "Seleccione una opcion: " ;
    int op;
    cin >> op;

    if (cin.fail()) {
        cin.clear(); // Entre el fail y el clear, se encargan de ver si falla la entrada (por pedir un int y que nos den otro tipo) y el clear "limpia" cin pa que no hayan errores
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //se ignoran la mayor cantidad de numeros que se encuentren hasta un salto de linea (el enter u espacio)
        throw invalid_argument("Entrada invalida, ingrese un numero");
    }

    return op;
}

void mostrarMenu(Tablero jugar){
    cout << "***************************************" << endl;
    cout << "Bienvenido al jogo mais grande do mundo" << endl;
    cout << "***************************************" << endl;
    cout << "" << endl;
    bool menu = true;

    while(menu){
        cout << "Seleccione una opcion:" << endl;
        cout << "> ";
        try {
            int opcion = mostrarOpciones();
            switch (opcion){
            case 0:
                cout << "Te rendiste!!!. Cerrando programa..." << endl;
                menu = false;
                break;

            case 1:
                cout << "No está disponible esta opcion. Intente nuevamente en otro momento..." << endl;
                break;

            case 2:
                jugar.mostrarTablero();
                cout << "" << endl;
                cout << "" << endl;
                break;

            case 3:
                cout << "Te la creiste xd, muy tonoto" << endl;
                break;
            
            default:
                cout << "Opción inválida. Intente nuevamente..." << endl;
                cout << " " << endl;
                cout << " " << endl;
                break;
            }

        } catch (const invalid_argument& e) {
            cout << e.what() << endl; //el what devuelve un mensaje descriptivo, establecido mas arriba
            cout << "Intentelo de nuevo"<< endl;
            cout << " " << endl;
        }
    }
}

int main(){

    Tablero jugar;
    mostrarMenu(jugar);

    return 0;
}