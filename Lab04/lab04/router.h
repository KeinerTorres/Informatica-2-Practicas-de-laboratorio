#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>
using namespace std;

/**
 * Clase Router.
 * Representa un enrutador dentro de la red, encargado de almacenar sus vecinos directos
 * y su tabla de enrutamiento (destino, costo total y ruta completa).
 */
class Router {
public:
    string nombre;
    map<string, int> vecinos;
    map<string, pair<int, vector<string>>> tablaEnrutamiento;

    Router();
    explicit Router(const string &nombre_);

    void agregarVecino(const string &vecino, int costo);
    void eliminarVecino(const string &vecino);
    void limpiarTabla();
    void actualizarEntrada(const string &destino, int costoTotal, const vector<string> &rutaCompleta);
    void mostrarTabla() const;
};

#endif
