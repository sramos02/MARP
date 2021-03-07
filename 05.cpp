//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
    int prof;
    int valor;
}Cofre;

typedef struct{
    int numSoluciones;
    int maxOro;
    int numObjetos;
    vector<Cofre> cofres;
}Solucion;

Solucion resolver(const int t, const int n, const Cofre valores[]) {
    Solucion tabla[n + 1][t + 1];

    //Caso base
    for(int i = 1; i <= n; i++) {
        tabla[0][i].numSoluciones = 1;
        tabla[i][0].maxOro = 0;
        tabla[i][0].numObjetos = 0;
    }

    for(int i = 0; i <= t; i++){
        tabla[0][i].numSoluciones = 0;
        tabla[0][i].maxOro = 0;
        tabla[0][i].numObjetos = 0;
    }

    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= t; j++) {
            if (3 * valores[i - 1].prof > j) //Si tardo demasiado en ir mejor no lo cojo
                tabla[i][j] = tabla[i - 1][j];
            else {
                int aux1 = tabla[i - 1][j].numSoluciones, aux2 = tabla[i - 1][j - (3 * valores[i - 1].prof)].numSoluciones;
                tabla[i][j].numSoluciones = aux1 + aux2;

                if (tabla[i - 1][j - 3 * valores[i - 1].prof].maxOro > tabla[i - 1][j].maxOro) { //Decide coger el camino
                    if (aux1 == 0 || aux2 != 0) {
                        tabla[i][j].numObjetos = tabla[i - 1][j - (3 * valores[i - 1].prof)].numObjetos + 1;
                        tabla[i][j].maxOro = tabla[i][j - (3 * valores[i].prof)].maxOro + valores[i].valor;
                        tabla[i][j].cofres = tabla[i - 1][j - (3 * valores[i - 1].prof)].cofres;
                        tabla[i][j].cofres.push_back(valores[i - 1]);
                    } else { //Decide no cogerlo
                        tabla[i][j].maxOro = tabla[i - 1][j].maxOro;
                        tabla[i][j].numObjetos = tabla[i - 1][j].numObjetos;
                        tabla[i][j].cofres = tabla[i - 1][j].cofres;
                    }
                }
                else {
                    if (aux1 != 0) {
                        tabla[i][j].maxOro = tabla[i - 1][j].maxOro;
                        tabla[i][j].numObjetos = tabla[i - 1][j].numObjetos;
                        tabla[i][j].cofres = tabla[i - 1][j].cofres;
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

    Solucion ret = resolver(t, n, valores);

    cout << ret.maxOro << endl << ret.numObjetos << endl;
    if (ret.cofres.size() > 0) {
        for (int i = 0; i < ret.cofres.size(); i++) cout << ret.cofres[i].prof << " " << ret.cofres[i].valor << "\n";
    }
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
