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


Solucion resolver(int t, int n, const Cofre valores[]) {
    Solucion tabla[n + 1][t + 1];
    Solucion ret;

    //Caso base
    for (int j = 0; j <= t; j++) {
        tabla[0][j].numSoluciones = 0;
        tabla[0][j].maxOro = 0;
        tabla[0][j].numObjetos = 0;
    }

    for (int i = 0; i <= n; i++) {
        tabla[i][0].numSoluciones = 1;
        tabla[i][0].maxOro = 0;
        tabla[i][0].numObjetos = 0;
    }


    for (int i = 1; i <= n; i++) {
        int prof = (3 * valores[i - 1].prof); //Tiempo que tardará en bajar
        for (int j = 1; j <= t; j++) {

            if (prof > j) //Si tardo demasiado en ir mejor no lo cojo
                tabla[i][j] = tabla[i - 1][j];
            else {
                int aux1 = tabla[i - 1][j].numSoluciones;
                int aux2 = tabla[i - 1][j - prof].numSoluciones;
                tabla[i][j].numSoluciones = aux1 + aux2;

                //Por defecto no cojo el camino
                tabla[i][j].maxOro = tabla[i - 1][j].maxOro;
                tabla[i][j].numObjetos = tabla[i - 1][j].numObjetos;
                tabla[i][j].cofres = tabla[i - 1][j].cofres;


                if (aux1 != 0 && aux2 != 0) { //Si tenemos las dos posibilidaddes buscamos la mejor
                    if (tabla[i - 1][j - prof].maxOro > tabla[i - 1][j].maxOro) {
                        tabla[i][j].numObjetos = tabla[i - 1][j - prof].numObjetos + 1;
                        tabla[i][j].maxOro = tabla[i - 1][j - prof].maxOro + valores[i - 1].valor;
                        tabla[i][j].cofres = tabla[i - 1][j - prof].cofres;
                        tabla[i][j].cofres.push_back(valores[i - 1]);
                    }
                } else if (aux2 != 0) {
                    tabla[i][j].numObjetos = tabla[i - 1][j - prof].numObjetos + 1;
                    tabla[i][j].maxOro = tabla[i - 1][j - prof].maxOro + valores[i - 1].valor;
                    tabla[i][j].cofres = tabla[i - 1][j - prof].cofres;
                    tabla[i][j].cofres.push_back(valores[i - 1]);
                }
                ret = tabla[i][j];
            }
        }
    }
    return ret;
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
    if (ret.cofres.size() > 0)
        for (int i = 0; i < ret.cofres.size(); i++)
            cout << ret.cofres[i].prof << " " << ret.cofres[i].valor << "\n";
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
