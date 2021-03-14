//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

//La solución priopuesta sigue el esquema de programación dinámica propuesto para el problema de las monedas.
//Se ha creado un tipo solución que almacenará la información relevante sobre las casillas de la tabla. Cada
//vez que una solución es mejor que una anterior se insertará en la tabla (siempre lleva el mínimo número de
//dardos posibles en la mejor solución). El coste del algoritmo es O(score*sections) en el caso peor tanto en
//espacio como en tiempo. Este algoritmo se podría mejorar en espacio utilizando solamente O(score) utilizando un
//solo vector que se iria actualizando de derecha a izquierda.

//Para que el resultado se actualice de manera adecuada es importante meter los elementos al principio del
//vector solución. De esta manera se insertan ordenadamente.


typedef struct {
    int numSoluciones;
    int numDardos;
    vector<int> resultado;
}Solucion;

Solucion resolver(const int score, const int sections, const int puntos[]) {
    Solucion tabla[sections+1][score+1];

    //Init
     for(int i = 1; i <= score; i++){
         tabla[0][i].numSoluciones = 0;
         tabla[0][i].numDardos = INT_MAX;
     }

    for(int i = 0; i <= sections; i++){
        tabla[i][0].numSoluciones = 1;
        tabla[i][0].numDardos = 0;
    }

    //Caso recursivo
    for(int i = 1; i <= sections; i++) {
        for(int j = 1; j <= score; j++) {

            //Si el tiro actual se pasa de remainingScore no lo cogemos
            if (puntos[i - 1] > j) tabla[i][j] = tabla[i - 1][j];
            else {
                int aux1 = tabla[i - 1][j].numSoluciones;
                int aux2 = tabla[i][j - puntos[i - 1]].numSoluciones;
                tabla[i][j].numSoluciones =  aux1 + aux2;

                if(aux1 != 0 && aux2 != 0) {
                    int minimo = min(tabla[i - 1][j].numDardos, tabla[i][j - puntos[i - 1]].numDardos + 1);
                    tabla[i][j].numDardos = minimo;
                    if (minimo == tabla[i][j - puntos[i - 1]].numDardos + 1) {
                        tabla[i][j].resultado = tabla[i][j - puntos[i - 1]].resultado;
                        tabla[i][j].resultado.insert(tabla[i][j].resultado.begin(), puntos[i - 1]);
                    }
                    else tabla[i][j].resultado = tabla[i-1][j].resultado;
                }
                else if (aux2 != 0) {
                    tabla[i][j].numDardos = tabla[i][j - puntos[i - 1]].numDardos + 1;
                    tabla[i][j].resultado = tabla[i][j - puntos[i - 1]].resultado;
                    tabla[i][j].resultado.insert(tabla[i][j].resultado.begin(), puntos[i - 1]);
                }
                else if (aux1 != 0){
                    tabla[i][j].numDardos = tabla[i - 1][j].numDardos;
                    tabla[i][j].resultado = tabla[i-1][j].resultado;
                }
            }
        }
    }
    return tabla[sections][score];
}

bool resuelveCaso() {
    int score; //[1-500]
    int sections; //[1-50]
    int shots[50];

    cin >> score >> sections;
    if (!cin) return false;

    for(int i = 0; i < sections; i++) cin >> shots[i];

    Solucion sol = resolver(score, sections, shots);
    if(sol.numSoluciones) {
        cout << sol.numDardos << ": ";
        for(int i : sol.resultado) cout << i << " ";
        cout << endl;
    }
    else cout << "Imposible\n";

    return true;
}

int main() {
    #ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
    #endif

    while (resuelveCaso());

    #ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif

    return 0;
}
