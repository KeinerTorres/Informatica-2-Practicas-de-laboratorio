#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <vector>
#include <fstream>
#include <string>

#include "Particula.h"
#include "Caja.h"
#include "Obstaculo.h"

class Simulador
{
private:
    double deltaTiempo;
    double tiempoActual;
    double tiempoFinal;
    double coeficienteRestitucionObstaculos;

    Caja cajaSimulacion;
    std::vector<Particula> listaDeParticulas;
    std::vector<Obstaculo> listaDeObstaculos;

    std::ofstream archivoEstados;
    std::ofstream archivoColisiones;

    void registrarEstadoActual();
    void registrarColision(const std::string &tipoColision,
                           int identificadorUno,
                           int identificadorDos,
                           const std::string &descripcionAdicional);

    void manejarColisionesConCaja();
    void manejarColisionesConObstaculos();
    void manejarColisionesEntreParticulas();
    void fusionarParticulas(Particula &particulaA,
                            Particula &particulaB);

public:
    Simulador(double valorDeltaTiempo,
              double valorTiempoFinal,
              const Caja &caja,
              double coeficienteRestitucion,
              const std::string &nombreArchivoEstados,
              const std::string &nombreArchivoColisiones);

    ~Simulador();

    void agregarParticula(const Particula &particula);
    void agregarObstaculo(const Obstaculo &obstaculo);

    void ejecutarPaso();
    void ejecutarSimulacion();
};

#endif // SIMULADOR_H

