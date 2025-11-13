#include "Simulador.h"
#include <iostream>
#include <cmath>
using namespace std;

Simulador::Simulador(double valorDeltaTiempo,
                     double valorTiempoFinal,
                     const Caja &caja,
                     double coeficienteRestitucion,
                     const string &nombreArchivoEstados,
                     const string &nombreArchivoColisiones)
    : deltaTiempo(valorDeltaTiempo),
    tiempoActual(0.0),
    tiempoFinal(valorTiempoFinal),
    coeficienteRestitucionObstaculos(coeficienteRestitucion),
    cajaSimulacion(caja)
{
    archivoEstados.open(nombreArchivoEstados);
    if (!archivoEstados.is_open())
    {
        cerr << "Error al abrir el archivo de estados.\n";
    }
    else
    {
        archivoEstados << "tiempo,id,x,y,vx,vy\n";
    }

    archivoColisiones.open(nombreArchivoColisiones);
    if (!archivoColisiones.is_open())
    {
        cerr << "Error al abrir el archivo de colisiones.\n";
    }
    else
    {
        archivoColisiones << "tiempo,tipo,id1,id2,descripcion\n";
    }
}

Simulador::~Simulador()
{
    if (archivoEstados.is_open())
        archivoEstados.close();
    if (archivoColisiones.is_open())
        archivoColisiones.close();
}

void Simulador::agregarParticula(const Particula &particula)
{
    listaDeParticulas.push_back(particula);
}

void Simulador::agregarObstaculo(const Obstaculo &obstaculo)
{
    listaDeObstaculos.push_back(obstaculo);
}

void Simulador::ejecutarPaso()
{
    for (Particula &particula : listaDeParticulas)
    {
        particula.actualizar(deltaTiempo);
    }

    manejarColisionesConCaja();
    manejarColisionesConObstaculos();
    manejarColisionesEntreParticulas();
    registrarEstadoActual();
    tiempoActual += deltaTiempo;
}

void Simulador::ejecutarSimulacion()
{
    while (tiempoActual <= tiempoFinal)
    {
        ejecutarPaso();
    }
}
