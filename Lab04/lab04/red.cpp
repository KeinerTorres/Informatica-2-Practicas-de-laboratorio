#include "Red.h"
#include <iostream>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

void Red::recalcularTablas() {
    for (auto &par : routers) {
        const string &origen = par.first;
        Router &routerOrigen = par.second;

        map<string, int> dist;
        map<string, string> padre;
        set<string> visitados;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> cola;

        for (const auto &otro : routers)
            dist[otro.first] = numeric_limits<int>::max();

        dist[origen] = 0;
        cola.push({0, origen});

        while (!cola.empty()) {
            auto [costoActual, nodoActual] = cola.top();
            cola.pop();
            if (visitados.count(nodoActual)) continue;
            visitados.insert(nodoActual);

            const Router &routerActual = routers[nodoActual];
            for (const auto &vec : routerActual.vecinos) {
                const string &vecino = vec.first;
                int peso = vec.second;
                if (dist[nodoActual] != numeric_limits<int>::max() &&
                    dist[nodoActual] + peso < dist[vecino]) {
                    dist[vecino] = dist[nodoActual] + peso;
                    padre[vecino] = nodoActual;
                    cola.push({dist[vecino], vecino});
                }
            }
        }

        routerOrigen.limpiarTabla();
        for (const auto &otro : routers) {
            const string &destino = otro.first;
            int costoTotal = dist[destino];
            vector<string> rutaCompleta;
            if (costoTotal != numeric_limits<int>::max()) {
                string actual = destino;
                rutaCompleta.push_back(actual);
                while (actual != origen) {
                    auto it = padre.find(actual);
                    if (it == padre.end()) break;
                    actual = it->second;
                    rutaCompleta.push_back(actual);
                }
                reverse(rutaCompleta.begin(), rutaCompleta.end());
            }
            routerOrigen.actualizarEntrada(destino, costoTotal, rutaCompleta);
        }
    }
}

void Red::agregarRouter(const string &nombre) {
    if (routers.find(nombre) == routers.end()) {
        routers.emplace(nombre, Router(nombre));
        recalcularTablas();
        cout << "Router " << nombre << " agregado." << endl;
    } else {
        cout << "El router " << nombre << " ya existe." << endl;
    }
}

void Red::eliminarRouter(const string &nombre) {
    if (routers.erase(nombre)) {
        for (auto &par : routers)
            par.second.eliminarVecino(nombre);
        recalcularTablas();
        cout << "Router " << nombre << " eliminado." << endl;
    } else {
        cout << "El router " << nombre << " no existe." << endl;
    }
}


void Red::conectarRouters(const string &r1, const string &r2, int costo) {
    auto it1 = routers.find(r1);
    auto it2 = routers.find(r2);

    if (it1 == routers.end() || it2 == routers.end()) {
        cout << "Uno o ambos routers no existen." << endl;
        return;
    }

    it1->second.agregarVecino(r2, costo);
    it2->second.agregarVecino(r1, costo);

    recalcularTablas();
    cout << "Conectados " << r1 << " <-> " << r2 << " (Costo: " << costo << ")" << endl;
}

void Red::actualizarCostoEnlace(const string &r1, const string &r2, int nuevoCosto) {
    conectarRouters(r1, r2, nuevoCosto);
}

void Red::desconectarRouters(const string &r1, const string &r2) {
    auto it1 = routers.find(r1);
    auto it2 = routers.find(r2);

    if (it1 == routers.end() || it2 == routers.end()) {
        cout << "Uno o ambos routers no existen." << endl;
        return;
    }

    it1->second.eliminarVecino(r2);
    it2->second.eliminarVecino(r1);

    recalcularTablas();
    cout << "Desconectados " << r1 << " y " << r2 << "." << endl;
}
