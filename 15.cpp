//Ejercicio 15
//Sergio Ramos Mesa
//María Esther Ruiz-Capillas Muñoz
//Germán Castaño Rolsán

#include <iostream>
#include <fstream>

#include <queue>
#include <vector>
#include "Matriz.h"
using namespace std;

struct tNodo {
    int calidad;
    int prioridad; //calidad estimada
    int profundidad; //carro actual
    vector<bool> marcasCaminos;
    //vector<bool> marcasCarros;

    bool operator<(tNodo const &otro) const { //Comparador de prioridades
        return otro.prioridad > prioridad;
    }
};

void calculaEstimado(int n, int m, Matriz<int> const& calidades, vector<int> & estim){

    for(int i = n - 1; i >= 0; i--) {
        int max = 0;
        for(int j = 0; j < m; j++) {
            if(calidades[i][j] > max)
                max = calidades[i][j];
        }

        if(i != n-1) estim[i] = max + estim[i+1];
        else estim[i] = max;
    }
}

int lasQuitanieves(vector<int> const& carros, vector<int> const& caminos, Matriz<int> const& calidades) {
    int n = carros.size(); //carros
    int m = caminos.size(); //caminos
    int mejorCalidad = -1;

    if(n != 0) {
        vector<int> estim(n);
        calculaEstimado(n, m, calidades, estim);

        //Inicializamos la cola de prioridad
        priority_queue<tNodo> cola = priority_queue<tNodo>();
        tNodo act;
        //act.marcasCarros = vector<bool>(n, false);
        act.marcasCaminos = vector<bool>(m, false);
        act.calidad = 0;
        act.prioridad = 0;
        act.profundidad = -1;
        cola.push(act);

        while (!cola.empty() && cola.top().prioridad > mejorCalidad) {
            act = cola.top();
            cola.pop();

            for (int j = 0; j < m; j++) { //recorre los caminos
                tNodo hijo(act);
                hijo.profundidad += 1;
                int i = hijo.profundidad;

                //Posible solución
                if (!act.marcasCaminos[j] && (carros[i] <= caminos[j])) {//!act.marcasCarros[i] &&
                    //hijo.marcasCarros[i] = true;
                    hijo.marcasCaminos[j] = true;

                    hijo.calidad = hijo.calidad + calidades[i][j];

                    hijo.prioridad = hijo.calidad;
                    if (i < n - 1) hijo.prioridad += estim[i + 1];

                    //Mejor solución (valor debe ser máximo y llgar al final)
                    if (hijo.prioridad > mejorCalidad) {
                        if (hijo.profundidad == n - 1)
                            mejorCalidad = hijo.calidad;
                        else cola.push(hijo);
                    }
                }
            }
        }
    }

    if(mejorCalidad >= 0) return mejorCalidad;
    else return 0; //Para el -1 (no encuentra ningun camino posible para ningun quitanieves)
}

bool resuelveCaso() {
    int n, m;
    cin >> n >> m;

    vector<int> carros(n);
    vector<int> caminos(m);
    Matriz<int> calidades(n, m, 0);

    for(int i = 0; i < n; i++) {
        cin >> carros[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> caminos[i];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> calidades[i][j];
        }
    }

    int ret = lasQuitanieves(carros, caminos, calidades);
    cout << ret << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casosQuitanieves.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    for(int i = 0; i < casos; i++)
        resuelveCaso();

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
