#include <iostream>
#include <fstream>
#include "Matriz.h"

#define max(a, b) a < b ? b : a

int laGorda(const int cubos[], Matriz<int> &tabla, int i, int j);

int miVaca(const int cubos[], Matriz<int> &tabla, int i, int j) {
    int &res = tabla[i][j];

    //casos base
    if(res != -1) return res; //ya calculado
    if(i == j) return cubos[i]; //solo queda un cubo
    if(i+1 == j) return max(cubos[i], cubos[j]); //quedan dos cubos

    //caso recursivo
    return max(laGorda(cubos, tabla, i+1, j) + cubos[i],
                  laGorda(cubos, tabla, i, j-1) + cubos[j]);
}

int laGorda(const int cubos[], Matriz<int> &tabla, int i, int j){
    int &res = tabla[i][j];

    //caso base
    if (res != -1) return res;

    //caso recursivo
    if (cubos[i] > cubos[j]) return miVaca(cubos, tabla, i+1, j);
    return miVaca(cubos, tabla, i, j-1);
}

bool resuelveCaso() {
    int n;

    std::cin >> n;
    if (n == 0) return false;
    int cubos[n];

    for (int i = 0; i < n; i++)
        std::cin >> cubos[i];

    Matriz<int> tabla(n, n, -1);
    std::cout << miVaca(cubos, tabla, 0, n-1) << std::endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
