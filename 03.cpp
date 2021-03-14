//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"
using namespace std;

typedef struct {
    int cont;
    int pos;
}tSolucion;

vector<int> maxCamino(int i, int n, const Matriz<int> & datos){
    vector<int> act = datos[i];
    vector<int> ant;

    if(i == 0) return act;
    ant = maxCamino(i-1, n, datos);

    for(int j = 0; j < n; j++){
        act[j] = ant[j];
        if(j != 0) act[j] = max(act[j], ant[j-1]);
        if(j != n-1) act[j] = max(act[j], ant[j+1]);
        act[j] += datos[i][j];
    }
    return act;
}

tSolucion resolver(int n, const Matriz<int> & datos) {
    tSolucion ret;
    ret.cont = 0;

    vector<int> fila = maxCamino(n-1, n, datos);
    for(int i = 0; i < n; i++)
        if(fila[i] > ret.cont){
            ret.cont = fila[i];
            ret.pos = i + 1;
        }

    return ret;
}

bool resuelveCaso() {
    int n;

    cin >> n; //Lectura de datos de entrada
    if (!cin) return false;
    Matriz<int> datos(n, n, 0);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            int aux;
            cin >> aux;
            datos[i][j] = aux;
        }

    tSolucion ret = resolver(n, datos);
    cout <<  ret.cont << " " << ret.pos << endl;

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
