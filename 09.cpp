//Sergio Ramos Mesa

#include <iostream>
#include <fstream>

#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

void cortesRecursivos(int i, int j, int cortes[], Matriz<EntInf> & tabla){
    int n = tabla.numcols() - 1;

    //Matriz<int> matrices(n+1,n+1,0), P = Matriz<int>(n+1,n+1,0);
    for (int d = 1; d <= n-1; ++d){// recorre diagonales
        for (int i = 1; i <= n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            tabla[i][j] = Infinito;
            for (int k = i; k <= j-1; ++k) {
                
            }
        }
    }

}

int losTablones(int n, int l, int cortes[]){
    Matriz<EntInf> tabla(n,n,0);
    cortesRecursivos(1, n, cortes, tabla);
}

bool resuelveCaso() {
    int l, n;
    int cortes[500];

    cin >> l >> n;
    if (!cin) return false;
    for (int i = 0; i < n; i++) {
        cin >> cortes[i];
    }

    int ret = losTablones(n, l, cortes);
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
