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
    char p1 = palabra[i], p2 = palabra[j];

    //Caso base
    if(i == j) return res;

    //Caso recursivo
    if (p1 == p2) res = resolver_rec(i + 1, j - 1, palabra, tabla);
    else res = min(resolver_rec(i, j - 1, palabra, tabla), resolver_rec(i + 1, j, palabra, tabla)) + 1;

    return res;
}

string reconstruir(int i, int j, const string palabra, Matriz<int> const & tabla){
    string res;

    //Caso base
    if (i == j) {
        res = palabra[i];
        return res;
    }

    //Caso recursivo
    if (palabra[i] == palabra[j]) {
        res.push_back(palabra[i]);
        reconstruir(i+1, j-1, palabra, tabla);
    }
    else {
        string res1 = reconstruir(i + 1, j, palabra, tabla);
        string res2 = reconstruir(i, j - 1, palabra, tabla);

        if(res1.length() < res2.length()){
            res = res1;
            res.push_back(palabra[i]);
        }
        else {
            res = res2;
            res.push_back(palabra[j]);
        }
    }

    return res;
}

bool resuelveCaso() {
    string p;

    cin >> p;
    if (!cin) return false;

    int n = p.length();
    Matriz<int> tabla(n,n,0);

    cout << resolver_rec(0,n-1, p, tabla) << " ";
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



/*
 * void solve_2(const int i, const int j, const string palabra, string & nueva) {
    string p1, p2, res1, res2;

    //Para hacer un insert debe ser string
    p1.push_back(palabra[i]);
    p2.push_back(palabra[j]);

    if(i == j) nueva = palabra;
    else{
        if (p1 == p2) {
            resolver_rec(i + 1, j - 1, palabra, nueva);
        }
        else {

            resolver_rec(i, j - 1, palabra, res1);
            resolver_rec(i + 1, j, palabra, res2);

            if (res1.length() <= res2.length()){
                nueva = res1;
                nueva.insert(i, p2);
            }
            else {
                nueva = res2;
                nueva.insert(j, p1);
            }
        }
    }
}
 * */
