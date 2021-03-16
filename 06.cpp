//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"
using namespace std;

//Es obvio que se tiene que quedar con la más corta. Izquierda o derecha
//Pero no se cuando elegir. He pensado en crear dos caminos, izq y der

//Elegir el que tenga la menor longitud. Esto es rentable?
string resolver_rec_4(int i, int j, int n, string palabra, Matriz<string> tabla) {
    string & res = tabla[i][j];

    char p1 = palabra[j];
    char p2 = palabra[n - i];

    //El valor ya se ha calculado
    if (res != "") return res;

    //Caso base
    if(i == n && j == n) {
        res.push_back(p1);
        return res;
    }

    //Caso recursivo
    if (i == n) { //Te has quedado sin letras con las que comparar
        res = resolver_rec_4(i, j+1, n, palabra, tabla);
        res.push_back(p1);
    }
    else{
        if(p1 == p2) { //Las letras son iguales
            res = resolver_rec_4(i + 1, j + 1, n, palabra, tabla);
            res.push_back(p2);
        } else { //Letras diferentes
            res = resolver_rec_4(i + 1, j, n, palabra, tabla);
            res.push_back(p2);
        }
    }
    return res;
}

string resolver(string palabra) {
    int n = palabra.length();
    Matriz<string> tabla(n,n,"");

    //return resolver_rec(0,0, n-1, palabra, tabla);
    //return resolver_rec_2(0,0, n-1, palabra, tabla);
    //return resolver_rec_3(0,0, 1, n-1, palabra, tabla);
    return resolver_rec_4(0,0, n-1, palabra, tabla);
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



/*string resolver_rec_3(int i, int j, int camino, int n, string palabra, Matriz<string> tabla) {
    string & res = tabla[i][j];

    char p1 = palabra[j];
    char p2 = palabra[n - i];

    //El valor ya se ha calculado
    if (res != "") return res;


    //Caso base
    if(i == n && j == n) {
        if(camino == 1) res.push_back(p1);
        else res.push_back(p2);
        return res;
    }

    //Caso recursivo
    if (camino == 1 && j == n) { //Te has quedado sin letras con las que comparar
        res = resolver_rec_3(i, j + 1, camino, n, palabra, tabla);
        res.push_back(p1);
    }
    else if (camino == 2 && i == n){
           res = resolver_rec_3(i+1, j, camino, n, palabra, tabla);
           res.push_back(p2);
    }
    else {
        if (p1 == p2) { //Las letras son iguales
            res = resolver_rec_3(i + 1, j + 1, camino, n, palabra, tabla);
            if (camino == 1) res.push_back(p2);
            else res.push_back(p1);
        } else { //Letras diferentes
            string res1 = resolver_rec_3(i + 1, j, 1, n, palabra, tabla);
            string res2 = resolver_rec_3(i, j + 1, 2, n, palabra, tabla);
            if (res1.length() <= res2.length()) {
                res = res1;
                res.push_back(p2);
            } else {
                res = res2;
                res.push_back(p1);
            }
        }
    }
    return res;
}

string resolver_rec_2(int i, int j, int n, string palabra, Matriz<string> tabla) {
    string & res = tabla[i][j];
    char p1 = palabra[j];
    char p2 = palabra[n - i];

    //El valor ya se ha calculado
    if (res != "") return res;


    //Caso base
    if(i == n && j == n) {
        res.push_back(p1);
        return res;
    }

    //Caso recursivo
    if (i == n) { //Te has quedado sin letras con las que comparar
        res = resolver_rec_2(i, j+1, n, palabra, tabla);
        res.push_back(p1);
    }
    else{
        if(p1 == p2) { //Las letras son iguales
            res = resolver_rec_2(i+1, j+1, n, palabra, tabla);
            res.push_back(p2);
        }
        else { //Letras diferentes
            res = resolver_rec_2(i + 1, j, n, palabra, tabla);
            res.push_back(p2);
        }
    }
    return res;
}

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
*/
