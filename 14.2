//Sergio Ramos Mesa
//German Castaño Roldan
// María Esther Ruiz-Capillas Muñoz

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

struct tNodo {
    EntInf tiempo;
    EntInf prioridad; //tiempo estimado
    int profundidad; //trabajador actual
    vector<bool> marcas;

    bool operator<(tNodo const &otro) const { //Comparador de prioridades
        return otro.prioridad < prioridad;
    }
};

void calculaOptimista(vector<EntInf> & estim, Matriz<int> const& tiempos){
    int n = tiempos.numfils();
    for(int i = n - 1; i >= 0; i--) {
        EntInf min = Infinito;
        for(int j = 0; j < n; j++) {
            if(EntInf(tiempos[i][j]) < min)
                min = tiempos[i][j];
        }

        if(i != n-1) estim[i] = min + estim[i+1];
        else estim[i] = min;
    }
}

void calculaPesimista(vector<EntInf> & estim, Matriz<int> const& tiempos){
    int n = tiempos.numfils();
    for(int i = n - 1; i >= 0; i--) {
        EntInf max = 0;
        for(int j = 0; j < n; j++) {
            if(EntInf(tiempos[i][j]) > max)
                max = tiempos[i][j];
        }

        if(i != n-1) estim[i] = max + estim[i+1];
        else estim[i] = max;
    }
}

//No se puede hacer recursivo, por ramificación y poda
EntInf laMochilita(Matriz<int> const& tiempos, int n){
    vector<EntInf> optimista(n);
    vector<EntInf> pesimista(n);

    calculaOptimista(optimista, tiempos); //Cota inferior
    calculaPesimista(pesimista, tiempos); //Cota superior

    EntInf mejorTiempo = pesimista[0];

    //Creamos la cola y creamos la raiz
    priority_queue<tNodo> cola = priority_queue<tNodo>();

    tNodo act;
    act.marcas = vector<bool>(n,false);
    act.tiempo = 0; act.prioridad = 0;
    act.profundidad = -1;
    cola.push(act);

    vector<int> mejorSol;
    while(!cola.empty() && cola.top().tiempo < mejorTiempo){

        //sacamos el valor de arriba y creamos una copia a prof+1
        act = cola.top();
        cola.pop();

        //recorre todos los tiempos posibles para cada trabajador
        //buscamos la mejor combinación
        for(int j = 0; j < n; j++) {
            tNodo hijo(act);
            hijo.profundidad += 1; //el nodo que estás calculando
            int i = hijo.profundidad;

            //Posible solución
            if (!act.marcas[j]){ //la tarea debe estar disponible y ser mejor
                hijo.marcas[j] = true; //el número que estamos cogiendo
                hijo.tiempo = hijo.tiempo + tiempos[i][j];

                //Esto es importante, no funcionaba sin el if, else
                if(i != n-1) hijo.prioridad = hijo.tiempo + optimista[i+1];
                else hijo.prioridad = hijo.tiempo;

                if(hijo.prioridad < mejorTiempo) {
                    //Si es solución, final de una rama
                    if (hijo.profundidad == n - 1) {
                        mejorTiempo = hijo.tiempo;
                    }
                    else {
                        cola.push(hijo);
                        mejorTiempo = min(mejorTiempo, hijo.tiempo + pesimista[hijo.profundidad]);
;                    }
                }
            }
            hijo.marcas[j] = false;
        }
    }
    return mejorTiempo;
}

bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0) return false;
    Matriz<int> tiempos(n,n,0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> tiempos[i][j];
    }

    cout << laMochilita(tiempos, n) << endl;
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
