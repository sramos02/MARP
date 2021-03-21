//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"
using namespace std;

//Es obvio que se tiene que quedar con la más corta. Izquierda o derecha
//Pero no se cuando elegir. He pensado en crear dos caminos, izq y der

//Elegir el que tenga la menor longitud. Esto es rentable?
int resolver_rec(const int i, const int j, const string palabra, Matriz<int> & tabla) {
    int & res = tabla[i][j];

    //Caso base
    if(i >= j) return res;

    //Caso recursivo
    if (palabra[i] == palabra[j])
        res = resolver_rec(i + 1, j - 1, palabra, tabla);
    else
        res = min(resolver_rec(i, j - 1, palabra, tabla), resolver_rec(i + 1, j, palabra, tabla)) + 1;

    return res;
}

string reconstruir(int i, int j, const string palabra, Matriz<int> const & tabla){
    string res, aux;

    //Caso base
    if(i >= j) return palabra;

    //Caso recursivo
    if (palabra[i] == palabra[j]) {
        res = reconstruir(i+1, j-1, palabra, tabla);
    }
    else if(tabla[i][j-1] < tabla[i+1][j]) {
        res = reconstruir(i, j - 1, palabra, tabla);
        aux.push_back(palabra[j]);
        res.insert(i, aux);
    }
    else {
        res = reconstruir(i + 1, j, palabra, tabla);
        aux.push_back(palabra[i]);
        res.insert(j+1+(tabla[i][j]-1), aux); //Esto hace que las nuevas cadenas entren en orden, sino las invierte
    }

    return res;
}

bool resuelveCaso() {
    string p;

    cin >> p;
    if (!cin) return false;

    int n = p.length();
    Matriz<int> tabla(n, n, 0);

    cout << resolver_rec(0, n-1, p, tabla) << " ";
    cout << reconstruir(0, n-1, p, tabla) << endl;
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
