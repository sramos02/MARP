#include <iostream>
#include <fstream>
#include "Matriz.h"


int laGorda(const int cubos[], Matriz<int> &tabla, int i, int j);

int getMax(int a, int b){
    return a < b ? b : a;
}

int miVaca(const int cubos[], Matriz<int> &tabla, int i, int j) {
    int &res = tabla[i][j];

    if(res == -1) {
        if (i == j) res = cubos[i];
        else if (i + 1 == j) res = getMax(cubos[i], cubos[j]);
        else res = getMax(laGorda(cubos, tabla, i + 1, j) + cubos[i],
                   laGorda(cubos, tabla, i, j - 1) + cubos[j]);
    }
    return res;
}

int laGorda(const int cubos[], Matriz<int> &tabla, int i, int j){
    int &res = tabla[i][j];

    if (res == -1) {
        if (cubos[i] > cubos[j]) res = miVaca(cubos, tabla, i + 1, j);
        else res = miVaca(cubos, tabla, i, j - 1);
    }
    return res;
}

bool resuelveCaso() {
    int n;

    std::cin >> n;

    if (n == 0)
        return false;

    int cubos[n];

    for (int i = 0; i < n; i++){
        std::cin >> cubos[i];
    }

    Matriz<int> tabla(n, n, -1);
    int sol = miVaca(cubos, tabla, 0, n-1);

    std::cout << sol << std::endl;

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
