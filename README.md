Alumnos:
Branco Abalos | 21.619.393-8 | C1 | branco.abalos@alumnos.ucn.cl
Eros Cortes | 19.949.826-6 | C1 | eros.cortes@alumnos.ucn.cl 
Joaquin Vega | 21.638.105-K | C2 | joaquin.vega02@alumnos.ucn.cl 

Comando usado en terminal/consola para que funcione:

(si es que no se encuentra por consola en "taller 2", usar cd "taller 2")

g++ -g main.cpp Tablero.cpp -o main 

./main

Documentacion

Explicación teórica del Minimax:

Minmax consiste en un algoritmo recursivo, en el que se toman decisiones pensando en que elegiremos  el mejor movimiento posible para nosotros mientras que nuestro oponente estará haciendo lo mismo.

Esto tiene ciertos requisitos, como que el juego al que se le aplique sea de dos jugadores, las acciones se tomen por turnos, ambos jugadores posean información completa del estado del juego y que 
funcione por un sistema de suma 0 (ambos jugadores tendrán cierto puntaje según qué tan cerca estén de lograr el objetivo del juego, si tu puntuación es alta, por consecuencia la de tu oponente debe ser baja),
juegos como “Gato”, el “Connect 4” o el “ajedrez” entran en esta categoría.

De forma gráfica, se deberán plantear todos los casos posibles desde donde nos encontremos hasta el final del juego, en el que se le darán valores por el desempeño logrado mediante la función de evaluación 
(un 1 contará como mejor decision/victoria para max, un -1 contará como mejor decision/victoria para min y el 0 indica un empate entre ambos). Al tener todas las casillas rellenadas en el nivel más abajo del árbol,
los niveles superiores a este elegirán el valor numérico adecuado de cada nodo terminal para el jugador que deba tomar la decisión de ese nivel del arbol (el valor positivo para max o el valor negativo para min).

![MiniMax](https://github.com/user-attachments/assets/0660c87b-034b-4c9b-8f17-5c38b5f64cbf)

Con tan solo un tablero de 3x3 los árboles generados son enormes, teniendo la fórmula de (N-1)! opciones posibles de forma generalizada en juegos del estilo “Gato” o “Connect 4”, con N siendo el tamaño del tablero 
(cantidad de casillas), por lo que se recurre a la Poda Alfa Beta para reducir la cantidad de casos

La complejidad del Minimax es de un O(r^p), con "r" siendo el factor de ramificacion y "p" siendo la profundidad máxima del arbol


Poda Alfa Beta:

La poda Alfa-Beta tiene el fin de reducir la evaluación de todas las ramas tomando en cuenta las que ya se van conociendo.

Consiste en mantener un intervalo de mejores jugadas encontradas, el jugador Max será el “Alfa” y el jugador Min será el “Beta”, el Alfa tendrá inicializado el menos infinito (el cual se reemplazará cuando encontremos
un valor mayor) y el Beta tendrá inicializado más infinito (el cual se reemplazará cuando encontremos un valor menor). Los valores de Alfa y Beta que contengan en un nodo se pasaran a sus hijos no terminales y luego de
esto se evaluaran si son necesarios hacer cambios según los hijos terminales del nodo al que estemos revisando y el tipo de nodo (si es un max o un min, cambiando alfa o beta respectivamente según sus condiciones) desde
los árboles de izquierda a derecha, de abajo hacia arriba.

Si en alguna iteración ocurriera que Alfa es mayor o igual que Beta, significa que el nodo actual no podrá mejorar el valor ya encontrado, por lo que se podaran nodos a la derecha (provenientes del mismo padre) del valor 
que causó esta interacción. Si se poda en un nodo Max se llamará poda Alfa mientras que si se poda en un nodo Min se llamará poda Beta.

La complejidad del Minimax con poda Alfa Beta es de O(r^(p/2)), con "r" siendo el factor de ramificacion y "p" siendo la profundidad máxima del arbol
