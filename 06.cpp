//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"
using namespace std;
#define DOMJUDGE

string resolver_rec(int i, int j, int n, string palabra, Matriz<string> tabla) {
    string & res = tabla[i][j];
    char p1 = palabra[j];
    char p2 = palabra[n - i];

    //El valor ya se ha calculado
    if (res != "") return res;


    //Caso base
    if(i == n && j == n) {
        res.push_back(p2);
        return res;
    }

    //Caso recursivo
    if (j == n) { //Te has quedado sin letras con las que comparar
        res = resolver_rec(i+1, j, n, palabra, tabla);
        res.push_back(p2);
    }
    else{
        if(p1 == p2) { //Las letras son iguales
                res = resolver_rec(i+1, j+1, n, palabra, tabla);
                res.push_back(p1);
        }
        else { //Letras diferentes
            res = resolver_rec(i, j + 1, n, palabra, tabla);
            res.push_back(p1);
        }
    }
    return res;
}

string resolver(string palabra) {
    int n = palabra.length();
    Matriz<string> tabla(n,n,"");
    return resolver_rec(0,0, n-1, palabra, tabla);
}

bool resuelveCaso() {
    string p;

    cin >> p;
    if (!cin) return false;

    cout <<  resolver(p) << endl;

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
