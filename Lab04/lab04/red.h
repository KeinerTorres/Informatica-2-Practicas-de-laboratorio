#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class Red {
private:
    map<string, Router> routers;
    void recalcularTablas();

public:
    void agregarRouter(const string &nombre);
    void eliminarRouter(const string &nombre);

    void conectarRouters(const string &r1, const string &r2, int costo);
    void actualizarCostoEnlace(const string &r1, const string &r2, int nuevoCosto);
    void desconectarRouters(const string &r1, const string &r2);

    bool existeRouter(const string &nombre) const;
    void mostrarEstadoRed() const;
    void mostrarTablasEnrutamiento() const;

    void mostrarRutaMinima(const string &origen, const string &destino) const;
};

#endif
