//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"
using namespace std;

typedef struct{
    int prof;
    int valor;
}Cofre;

void reconstruir(vector<Cofre> & ret, const Matriz<int> & tabla, int t, int n, int i, int j, const Cofre valores[]) {
    if(i != 0) {
        int remTime = (3 * valores[i - 1].prof);

        if (remTime <= j && tabla[i - 1][j] < (tabla[i - 1][j - remTime]) + valores[i - 1].valor) {
            reconstruir(ret, tabla, t, n, i - 1, j - remTime, valores);
            ret.push_back(valores[i - 1]);
        } else {
            reconstruir(ret, tabla, t, n, i - 1, j, valores);
        }
    }
}

int resolver(Matriz<int> & tabla, int t, int n, const Cofre valores[]) {
    int remTime;
    int aux1, aux2;

    //Caso base
    for (int j = 0; j <= t; j++)
        tabla[0][j] = 0;

    for (int i = 0; i <= n; i++)
        tabla[i][0] = 0;


    for (int i = 1; i <= n; i++) {
        remTime = (3 * valores[i - 1].prof);
        for (int j = 1; j <= t; j++) {
            if (remTime > j)
                tabla[i][j] = tabla[i - 1][j]; //Si tardo demasiado en ir mejor no lo cojo
            else {
                aux1 = tabla[i - 1][j];
                aux2 = tabla[i - 1][j - remTime];

                if(aux1 > (aux2 + valores[i-1].valor)) tabla[i][j] = aux1;
                else{
                    tabla[i][j] = aux2;
                    tabla[i][j] += valores[i-1].valor;
                }
            }
        }
    }

    return tabla[n][t];
}

bool resuelveCaso() {
    int t, n;
    Cofre valores[100];

    cin >> t >> n;
    if (!cin) return false;
    for (int i = 0; i < n; i++) {
        cin >> valores[i].prof;
        cin >> valores[i].valor;

    }

    vector<Cofre> ret;
    Matriz<int> tabla(n+1, t+1, 0);
    int maxOro = resolver(tabla, t, n, valores);
    reconstruir(ret, tabla, t, n, n, t, valores);

    cout << maxOro << endl << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i].prof << " " << ret[i].valor << "\n";
    cout << "---" << endl;
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
