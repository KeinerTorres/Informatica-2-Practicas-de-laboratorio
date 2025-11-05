#include "Router.h"
#include <iomanip>
#include <algorithm>
using namespace std;

Router::Router() = default;

Router::Router(const string &nombre_) : nombre(nombre_) {}

void Router::agregarVecino(const string &vecino, int costo) {
    vecinos[vecino] = costo;
}

void Router::eliminarVecino(const string &vecino) {
    vecinos.erase(vecino);
}

void Router::limpiarTabla() {
    tablaEnrutamiento.clear();
}

void Router::actualizarEntrada(const string &destino, int costoTotal, const vector<string> &rutaCompleta) {
    tablaEnrutamiento[destino] = {costoTotal, rutaCompleta};
}

void Router::mostrarTabla() const {
    cout << "Tabla de enrutamiento del router " << nombre << ":" << endl;
    cout << left << setw(12) << "Destino" << setw(8) << "Costo" << "Ruta completa" << endl;
    for (const auto &entrada : tablaEnrutamiento) {
        const string &dest = entrada.first;
        int costo = entrada.second.first;
        const vector<string> &ruta = entrada.second.second;
        cout << left << setw(12) << dest;
        if (costo == numeric_limits<int>::max()) {
            cout << setw(8) << "INF" << "-";
        } else {
            cout << setw(8) << costo;
            for (size_t i = 0; i < ruta.size(); ++i) {
                cout << ruta[i];
                if (i + 1 < ruta.size()) cout << " -> ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
