//Sergio Ramos Mesa

#include <iostream>
#include <fstream>

#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

typedef struct{
    string horaIni;
    int duracion;
}tDatos;

int lasPeliculas(int n, vector<tDatos> datos){
    vector<int> parrafo(n);

    //Casos básicos
    int i = n-1;
    int suma = datos[i].horaIni + datos[i].duracion + 10; //Como hago esto?

    while (i >= 0 && ((n-1)-i) + suma <= L) {
        parrafo[i] = 0;
        --i;
        suma += l[i];
    }

    // casos recursivos
    while (i >= 0) {
        int j = i;
        suma = l[i];
        parrafo[i] = INF;

        while (j < n-1 && (j-i) + suma <= L) {
            int pen = L - (j-i) - suma;
            int nuevo = pen*pen*pen + parrafo[j+1];

            if (nuevo < parrafo[i]) parrafo[i] = nuevo;
            ++j;
            suma += l[j];
        }
        --i;
    }
    return parrafo[0];
}

bool resuelveCaso() {
    int n;
    vector<tDatos> cartelera;

    cin >> n;
    if (n == 0) return false;

    for (int i = 0; i < n; i++) {
        tDatos nuevo;
        cin >> nuevo.horaIni >> nuevo.duracion;
        cartelera.push_back(nuevo);
    }

    cout << lasPeliculas(n, cartelera) << endl;
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
