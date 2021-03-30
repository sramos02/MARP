//Sergio Ramos Mesa

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

struct tNodo {
    //ToDo tiempoEstimado
    EntInf tiempo;
    EntInf prioridad;
    int profundidad; //trabajador actual

    vector<bool> marcas;

    bool operator<(tNodo const &otro) const { //CoMparador de prioridades
        return otro.prioridad < prioridad;
    }
};

//No se puede hacer recursivo, por ramificación y poda
EntInf laMochilita(Matriz<int> const& tiempos, int n){
    EntInf mejorTiempo = Infinito;

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
            if (act.tiempo + tiempos[i][j] < mejorTiempo && !act.marcas[j]){ //la tarea debe estar disponible y ser mejor
                hijo.marcas[j] = true; //el número que estamos cogiendo
                hijo.tiempo = hijo.tiempo + tiempos[i][j];
                hijo.prioridad = hijo.tiempo;

                //Si es solución, final de una rama
                if(hijo.profundidad == n-1)
                    mejorTiempo = hijo.tiempo;
                else cola.push(hijo);
            }
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

    EntInf tiempo = Infinito;
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
