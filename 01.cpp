//Sergio Ramos Mesa

// Comentario general sobre la solución explicando cómo se resuelve el problema

//El problema ha sido resuelto utilizando el esquema de programación dinamica de las monedas
//La base del ejercicio consiste en distinguir si nos interesa coger una cuerda o no cogerla
//Si cogemos una cuerda entonces no se puede volver a coger por lo que siempre pasamos a la
//fila anterior de la matriz.

//La solución se ha conseguido en coste O(n*len) tanto en tiempo como en espacio adicional. El
//coste de rellenar la tabla. El coste de consulta es de O(n).

//Caso recursivo
// tabla[i][j] = min(tabla[i - 1][j], tabla[i - 1][j - cuerdas[i - 1]]) para el coste y las cuerdas
// tabla[i][j] = tabla[i - 1][j] + tabla[i - 1][j - cuerdas[i - 1]] para el numero de soluciones

//Casos base
// tabla[i][0] = 0 No queda longitud que cubrir
// tabla[0][i] = 0 No quedan cuerdas

//0 <= i <= n
//0 <= j <= len


#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>

//#define DOMJUDGE

typedef struct{
    long long int numSoluciones;
    int minCuerdas;
    long long int minCoste;
}Solucion;

Solucion resolver(int len, int n, const int cuerdas[], const int costes[]) {
    Solucion tabla[1001][1001];
    //Casos base
    for (int i = 0; i <= len; i++) {
        tabla[0][i].numSoluciones = 0;
        tabla[0][i].minCuerdas = INT_MAX;
        tabla[0][i].minCoste = INT_MAX;
    }
    for (int i = 0; i <= n; i++) {
        tabla[i][0].numSoluciones = 1;
        tabla[i][0].minCuerdas = 0;
        tabla[i][0].minCoste = 0;
    }

    //Caso recursivo
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= len; j++) {
            if (cuerdas[i - 1] > j)  //Si remDist < longCuerda
                 tabla[i][j] = tabla[i - 1][j];
            else { //Ahora solo tenemos en cuenta los caminos que son buenos
                long long int aux1 = tabla[i - 1][j].numSoluciones, aux2 = tabla[i - 1][j - cuerdas[i - 1]].numSoluciones;
                tabla[i][j].numSoluciones =  aux1 + aux2;

                if (aux1 > 0 && aux2 > 0) {
                    tabla[i][j].minCuerdas = std::min(tabla[i-1][j].minCuerdas, tabla[i - 1][j - cuerdas[i - 1]].minCuerdas + 1);
                    tabla[i][j].minCoste = std::min(tabla[i-1][j].minCoste, tabla[i - 1][j - cuerdas[i - 1]].minCoste + costes[i-1]);
                }
                else if (aux1 > 0) { //Si es solución no coger la cuerda
                    tabla[i][j].minCuerdas = tabla[i - 1][j].minCuerdas;
                    tabla[i][j].minCoste = tabla[i - 1][j].minCoste;
                }
                else if (aux2 > 0) { //Si es solución coger la cuerda
                    tabla[i][j].minCuerdas = tabla[i - 1][j - cuerdas[i - 1]].minCuerdas + 1;
                    tabla[i][j].minCoste = tabla[i - 1][j - cuerdas[i - 1]].minCoste + costes[i-1];
                }
                else {
                    tabla[i][j].minCuerdas = 0;
                    tabla[i][j].minCoste = 0;
                }
            }
        }
    }
    return tabla[n][len];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, longitud;
    int cuerdas[1000], costes[1000];

    std::cin >> n >> longitud;
    if (!std::cin) return false;

    for(int i = 0; i < n; i++) {
        std::cin >> cuerdas[i];
        std::cin >> costes[i];
    }

    Solucion sol = resolver(longitud, n, cuerdas, costes);
    if(sol.numSoluciones)
        std::cout << "SI " << sol.numSoluciones << " " << sol.minCuerdas << " " << sol.minCoste << std::endl;
    else std::cout << "NO\n";

    return true;
}


int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
