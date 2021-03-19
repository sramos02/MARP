//Sergio Ramos Mesa

#include <iostream>
#include <fstream>

#include "Matriz.h"
using namespace std;

typedef struct{
    string primero;
    string segundo;
}tRel;

int gradosSeparacion(int n, const tRel grafo[]){
   
}

bool resuelveCaso() {
    int r, n;
    tRel relaciones[500];

    cin >> n >> r;
    if (!cin) return false;
    for (int i = 0; i < n; i++) {
        cin >> relaciones[i].primero;
        cin >> relaciones[i].segundo;
    }

    int ret = gradosSeparacion(n, relaciones);
    (ret == 0)? cout << "DESCONECTADA":cout << ret;
    cout << endl;
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
