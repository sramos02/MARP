//Sergio Ramos Mesa

#include <iostream>
#include <fstream>

#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

EntInf buscaCortes(vector<int> const& cortes){
    int n = cortes.size() - 1;

    Matriz<EntInf> matrices(n+1,n+1,0);

    for (int d = 1; d < n; ++d){// recorre diagonales
        for (int i = 1; i < (n - d + 1); ++i) { // recorre elementos de diagonal
            int j = i + d;
            matrices[i][j] = Infinito;

            //Busca la mínima k de entre todas las posibles
            for (int k = i; k < j; ++k) {
                EntInf esfuerzo = (matrices[i][k] + matrices[k+1][j] + (2*cortes[k])); //(cortes[i-1] * cortes[k] * cortes[j]);
                if (esfuerzo < matrices[i][j]) matrices[i][j] = esfuerzo;
            }
        }
    }
    return matrices[1][n];
}


bool resuelveCaso() {
    int l, n;
    vector<int> cortes;

    cin >> l >> n;
    if (l == 0 && n == 0) return false;

    for (int i = 0; i < n; i++) {
        int aux; cin >> aux;
        cortes.push_back(aux);
    }

    EntInf ret = buscaCortes(cortes);

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



/*
//Sergio Ramos Mesa

#include <iostream>
#include <fstream>

#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

EntInf buscaCortes(vector<int> const& cortes, int len){
    int n = cortes.size() - 1;

    Matriz<EntInf> matrices(n+1,n+1,0);

    for (int i = n; i >= 0; i--){
        for (int j = i+1; j < n; j++) { //si i = j diagonal principal vale 0
            matrices[i][j] = Infinito;

            //Busca la mínima k de entre todas las posibles
            for (int k = i; k < n; k++) {
                EntInf aux1 = matrices[i][k], aux2 = matrices[k+1][j];
                EntInf esfuerzo = aux1 + aux2;

                if(aux1 == aux2) esfuerzo = esfuerzo + 2*len;
                else esfuerzo =  esfuerzo + 2*cortes[k]; //len=10  -> corte en 6 -> len1=6,len2=4

                if (esfuerzo < matrices[i][j])
                    matrices[i][j] = esfuerzo;
            }
        }
    }
    return matrices[1][n];


}

bool resuelveCaso() {
    int l, n;
    vector<int> cortes;

    cin >> l >> n;
    if (l == 0 && n == 0) return false;

    for (int i = 0; i < n; i++) {
        int aux; cin >> aux;
        cortes.push_back(aux);
    }

    cout << buscaCortes(cortes, l) << endl;
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
*/
