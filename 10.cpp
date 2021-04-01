//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>

#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

typedef struct{
    int iniTime; //convertido a segunos
    int duracion;
}tDatos;


int convierteSegundos(int hh, int mm){
    return hh*3600 + mm*60;
}

int horaFin(tDatos dato){
    return dato.iniTime + (dato.duracion + 10)*60;
}

//devuelve el máximo de minutos que se está viendo una película al
//considerar las pelis desde 1 a i que podemos ver antes de la hora j
int pelis(int n, vector<tDatos> const& datos){
    int max = 0;

    for(int i = 0; i < datos.size()-1; i++) {
        int aux = 0, j = i;
        bool fin = false;

        while ((j < datos.size()) && !fin){
            (horaFin(datos[j]) < datos[j + 1].iniTime) ? (aux += datos[j].duracion) : fin; //Tienen que estar encadenadas
            j++;
        }
        if(j == datos.size()-1) aux += datos[datos.size()-1].duracion;
    }
    return max;
}

bool resuelveCaso() {
    int n;
    vector<tDatos> cartelera;

    cin >> n;
    if (n == 0) return false;

    for (int i = 0; i < n; i++) {
        tDatos nuevo;
        string dato;

        cin >> dato >> nuevo.duracion;

        stringstream hora; hora << dato[0]; hora << dato[1]; //Preparo las horas
        stringstream min; min << dato[3]; min << dato[4];

        int intHora, intMin;
        hora >> intHora; min >> intMin;
        nuevo.iniTime = convierteSegundos(intHora, intMin);

        cartelera.push_back(nuevo);
    }

    cout << pelis(n, cartelera) << endl;
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
