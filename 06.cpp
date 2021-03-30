//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>

#include "Matriz.h"
using namespace std;

//Si las letras coinciden nos movemos en diagonal (siguientes 2 letras)
//Si no conciden nos quedamos con el mejor camino (Izq o Drc)
int resolver_rec(int i, int j, string const& palabra, Matriz<int> & tabla) {
    int & res = tabla[i][j];

    if(res == -1) {
        if (i >= j) res = 0;
        else {
            if (palabra[i] == palabra[j])
                res = resolver_rec(i + 1, j - 1, palabra, tabla);
            else
                res = min(resolver_rec(i, j - 1, palabra, tabla), resolver_rec(i + 1, j, palabra, tabla)) + 1;
        }
    }
    return res;
}

//Cuando los iteradores se cruzan se crea la palabra entera y por recursión
//va introduciendo los nuevos caracteres donde toque
string reconstruir(int i, int j, string const& palabra, Matriz<int> const& tabla){
    string res;

    //Caso base
    if(i >= j) res = palabra;
    else {
        if (palabra[i] == palabra[j]) {
            res = reconstruir(i + 1, j - 1, palabra, tabla);
        } else if (tabla[i][j - 1] < tabla[i + 1][j]) {
            res = reconstruir(i, j - 1, palabra, tabla);
            res.insert(i, 1, palabra[i]);
        } else {
            res = reconstruir(i + 1, j, palabra, tabla);
            res.insert(j + 1 + (tabla[i][j] - 1), 1, palabra[i]);
            //Esto hace que las nuevas cadenas entren en orden, sino las invierte
            //Básicamente le quita la longitud de lo ya introduciendo en ese bloque
        }
    }

    return res;
}

bool resuelveCaso() {
    string p;

    cin >> p;
    if (!cin) return false;

    int n = p.length();
    Matriz<int> tabla(n, n, -1);

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




/*
//Cuando los iteradores se cruzan para
//Si no, escribe la letra al principio, llama a reursión y luego la vuelve a escribir
string reconstruir(int i, int j, string const& palabra, Matriz<int> const& tabla){
    string res;

    //Caso base
    if(i == j) res = palabra[i];
    else if (i > j) res = "";
    else {
        if (palabra[i] == palabra[j]) {
            res.push_back(palabra[j]);
            res.insert(res.length(), reconstruir(i + 1, j - 1, palabra, tabla));
            res.push_back(palabra[j]);
        }
        else if (tabla[i][j - 1] < tabla[i + 1][j]) {
            res.insert(0, 1, palabra[j]);
            res.insert(res.length(), reconstruir(i, j - 1, palabra, tabla));
            res.insert(res.length(), 1, palabra[j]);
        }
        else {
            res.insert(0, 1, palabra[i]);
            res.insert(res.length(), reconstruir(i + 1, j, palabra, tabla));
            res.insert(res.length(), 1, palabra[i]);
        }
    }

    return res;
}
*/
