//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Matriz.h"
using namespace std;

int resolver_rec(const string & p1, const string & p2, int i, int j, Matriz<int> & tabla){
    int & res = tabla[i][j];

    //Caso base
    if (res != -1) return res; //El valor ya se ha calculado (inicializacion a 0)

    //Caso recursivo, si diferentes entonces busca el maximo
    if(p1[i] == p2[j]) res = resolver_rec(p1, p2, i-1, j-1, tabla) + 1;
    else res = max(resolver_rec(p1, p2, i-1, j, tabla), resolver_rec(p1, p2, i, j-1, tabla));
    return res;
}


//Sigue el procedimiento de resolver_rec
//nuevo es el nuevo caracter (vacio o una letra si p1[i] == p2[j])
//recursion contiene el string que vamos acarreando
string reconstruir(const string & p1, const string & p2, int i, int j, const Matriz<int> & tabla) {
    if(i < 0 || j < 0) return "";

    string nuevo = "";
    string recursion;

    if (p1[i] == p2[j]) {
        nuevo = p1[i];
        recursion =  reconstruir(p1, p2, i-1, j-1, tabla);
    }
    else {
        if (i == 0) recursion = reconstruir(p1, p2, i, j-1, tabla);
        else if(j == 0) recursion = reconstruir(p1, p2, i - 1, j, tabla);
        else{
            if (max(tabla[i - 1][j], tabla[i][j - 1]) == tabla[i - 1][j])
                recursion = reconstruir(p1, p2, i - 1, j, tabla);
            else recursion = reconstruir(p1, p2, i, j - 1, tabla);
        }

    }
    return recursion + nuevo;
}

string resolver(const string & p1, const string & p2) {
    Matriz<int> tabla(p1.length() + 1, p2.length() + 1, -1);

    //Casos base para la recursión
    for(int i = 0; i <= p1.length(); i++)
        tabla[i][0] = 0;

    for(int j = 0; j <= p2.length(); j++)
        tabla[0][j] = 0;

    resolver_rec(p1, p2, p1.length(), p2.length(), tabla);
    return reconstruir(p1, p2, p1.length()-1, p2.length()-1, tabla);
}

bool resuelveCaso() {
    string p1, p2;

    cin >> p1 >> p2; //Lectura de datos de entrada
    if (!cin) return false;

    cout <<  resolver(p1, p2) << endl;

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