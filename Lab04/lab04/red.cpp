#include "Red.h"
#include <iostream>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
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

bool Red::existeRouter(const string &nombre) const {
    return routers.find(nombre) != routers.end();
}

void Red::mostrarEstadoRed() const {
    cout << "\n    Estado actual de la red   " << endl;
    for (const auto &par : routers) {
        const string &nombre = par.first;
        const Router &r = par.second;
        cout << nombre << " conectado a: ";
        if (r.vecinos.empty()) {
            cout << "(sin conexiones)";
        } else {
            bool primero = true;
            for (const auto &vec : r.vecinos) {
                if (!primero) cout << ", ";
                cout << vec.first << "(" << vec.second << ")";
                primero = false;
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Red::mostrarTablasEnrutamiento() const {
    cout << "\n   Tablas de enrutamiento de la red   " << endl;
    for (const auto &par : routers) {
        par.second.mostrarTabla();
    }
}

void Red::mostrarRutaMinima(const string &origen, const string &destino) const {
    auto itOrigen = routers.find(origen);
    auto itDestino = routers.find(destino);
    if (itOrigen == routers.end() || itDestino == routers.end()) {
        cout << "Uno o ambos routers no existen." << endl;
        return;
    }

    const Router &r = itOrigen->second;
    auto it = r.tablaEnrutamiento.find(destino);
    if (it == r.tablaEnrutamiento.end() || it->second.first == numeric_limits<int>::max()) {
        cout << "No existe una ruta entre " << origen << " y " << destino << "." << endl;
        return;
    }

    const int costoTotal = it->second.first;
    const vector<string> &ruta = it->second.second;

    cout << "\nCamino mas corto de " << origen << " a " << destino
         << " (costo total: " << costoTotal << "):" << endl;
    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << ruta[i];
        if (i + 1 < ruta.size()) cout << "\n|\n";
    }
    cout << endl;
}

bool Red::cargarDesdeArchivo(const string &rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << rutaArchivo << "." << endl;
        return false;
    }

    string linea;
    int n = 0, m = 0;

    auto trim = [](string s) {
        size_t i = s.find_first_not_of(" \t\r\n");
        size_t j = s.find_last_not_of(" \t\r\n");
        if (i == string::npos) return string();
        return s.substr(i, j - i + 1);
    };


    while (getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty() || linea[0] == '#') continue;
        stringstream ss(linea);
        if (ss >> n >> m) break;
        cout << "Formato incorrecto en la cabecera (se esperaba: N M)." << endl;
        return false;
    }

    if (n <= 0 || m < 0) {
        cout << "Valores invalidos de N o M." << endl;
        return false;
    }


    routers.clear();


    int leidos = 0;
    while (leidos < n && getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty() || linea[0] == '#') continue;
        routers.emplace(linea, Router(linea));
        ++leidos;
    }
    if (leidos != n) {
        cout << "Numero de routers declarado no coincide con los nombres provistos." << endl;
        return false;
    }


    int enlaces = 0;
    while (enlaces < m && getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty() || linea[0] == '#') continue;

        string u, v;
        int w;
        stringstream ss(linea);
        if (!(ss >> u >> v >> w)) {
            cout << "Linea de enlace invalida: " << linea << endl;
            return false;
        }
        auto itU = routers.find(u);
        auto itV = routers.find(v);
        if (itU == routers.end() || itV == routers.end()) {
            cout << "Enlace referencia routers inexistentes: " << u << " " << v << endl;
            return false;
        }
        itU->second.agregarVecino(v, w);
        itV->second.agregarVecino(u, w);
        ++enlaces;
    }
    if (enlaces != m) {
        cout << "Numero de enlaces leidos no coincide con M." << endl;
        return false;
    }

    recalcularTablas();
    cout << "Red cargada correctamente desde " << rutaArchivo << "." << endl;
    return true;
}

bool Red::guardarEnArchivo(const string &rutaArchivo) const {
    ofstream out(rutaArchivo);
    if (!out.is_open()) {
        cout << "No se pudo abrir el archivo " << rutaArchivo << " para escritura." << endl;
        return false;
    }

    int n = static_cast<int>(routers.size());
    int m = 0;


    for (const auto &par : routers) {
        const string &u = par.first;
        const Router &ru = par.second;
        for (const auto &vec : ru.vecinos) {
            const string &v = vec.first;
            if (u < v) ++m;
        }
    }

    out << n << " " << m << "\n";

    // Nombres de routers
    for (const auto &par : routers) {
        out << par.first << "\n";
    }


    for (const auto &par : routers) {
        const string &u = par.first;
        const Router &ru = par.second;
        for (const auto &vec : ru.vecinos) {
            const string &v = vec.first;
            int w = vec.second;
            if (u < v) {
                out << u << " " << v << " " << w << "\n";
            }
        }
    }

    cout << "Red guardada correctamente en " << rutaArchivo << "." << endl;
    return true;
}

void Red::generarRedAleatoria(int numeroRouters, double densidadEnlaces,
                              int costoMinimo, int costoMaximo) {
    if (numeroRouters <= 0) {
        cout << "El numero de routers debe ser positivo." << endl;
        return;
    }
    if (densidadEnlaces < 0.0 || densidadEnlaces > 1.0) {
        cout << "La densidad debe estar en el rango [0, 1]." << endl;
        return;
    }
    if (costoMinimo <= 0 || costoMaximo < costoMinimo) {
        cout << "Rango de costos invalido." << endl;
        return;
    }

    routers.clear();


    for (int i = 1; i <= numeroRouters; ++i) {
        string nombre = "R" + to_string(i);
        routers.emplace(nombre, Router(nombre));
    }


    mt19937 rng(random_device{}());
    uniform_int_distribution<int> distCosto(costoMinimo, costoMaximo);
    uniform_real_distribution<double> distProb(0.0, 1.0);


    for (int i = 1; i < numeroRouters; ++i) {
        string a = "R" + to_string(i);
        string b = "R" + to_string(i + 1);
        int w = distCosto(rng);
        routers[a].agregarVecino(b, w);
        routers[b].agregarVecino(a, w);
    }


    for (int i = 1; i <= numeroRouters; ++i) {
        for (int j = i + 1; j <= numeroRouters; ++j) {
            string a = "R" + to_string(i);
            string b = "R" + to_string(j);
            if (routers[a].vecinos.count(b) == 0) {
                if (distProb(rng) < densidadEnlaces) {
                    int w = distCosto(rng);
                    routers[a].agregarVecino(b, w);
                    routers[b].agregarVecino(a, w);
                }
            }
        }
    }

    recalcularTablas();
    cout << "Se genero una red aleatoria con " << numeroRouters << " routers." << endl;
}
