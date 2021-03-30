//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

EntInf floyd(Matriz<int> const& G, int i, int j, const int n) {
    EntInf ret = Infinito; //Inicializamos a infinito para encontrar el camino menor

    if(j == n-1) ret = 1; //caso base, ha llegado al final
    else {
        //si no está en el final recorre la columna en busca del menor número
        //de conexiones posibles
        for (int k = i + 1; k < n; ++k) {
            if (G[k][j] != 0) {
                EntInf temp = floyd(G, j, k, n);
                if (temp < ret) ret = temp + 1;
            }
        }
    }

  return ret;
}


bool resuelveCaso() {
    int r, n;
    cin >> n >> r;
    if (!cin) return false;

    int numVertices = 0;
    unordered_map<string, int> grafo;
    Matriz<int> ady(n,n,0);

    for (int i = 0; i < r; i++) {
        string key1, key2;
        cin >> key1 >> key2;

        if(grafo.find(key1) == grafo.end()) {
            grafo[key1] = numVertices;
            numVertices++;
        }
        if(grafo.find(key2) == grafo.end()) {
            grafo[key2] = numVertices;
            numVertices++;
        }
        ady[grafo.at(key1)][grafo.at(key2)] += 1; //La matriz es simetrica solo rellenamos la mitad
        ady[grafo.at(key2)][grafo.at(key1)] += 1;
    }

    EntInf res = floyd(ady, 0, 1, n);
    if(res == Infinito) cout << "DESCONECTADA\n";
    else cout << res << endl;

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



/*Como es un poco complicado de ver voy a poner un ejemplo de ejecución
 *Imaginemos las siguientes relaciones:
 *
 * Marta Mario
 * Mario Roberto
 * Roberto Raquel
 * Mario Raquel
 *
 * La matriz de adyacencia quedaría de la siguiente manera:
 *
 * 0 1 0 0
 * 1 0 1 1
 * 0 1 0 1
 * 0 1 1 0  //Tenemos en cuenta que es simétrica
 *
 * empezando en la columna 1 (porque solo nos interesa leer por encima de la diagonal principal)
 * recorremos toda la columna buscando más de una relación (sino estaría desconectado)
 * Cuando encontramos varias vamos calculando el mínimo del coste para llegar, inicializado a infinito
 *
 * Es importante la llamada recursiva a la traspuesta (para volver a la diagonal principal)
*/

