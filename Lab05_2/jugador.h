#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Proyectil.h"

class Jugador
{
public:
    std::string nombre;
    int proyectilesLanzados;

    float x;
    float y;
    int teclaPermitida;
    int teclaNoPermitida;

    Jugador(const std::string &nombreJugador, float posX, float posY);

    Proyectil* lanzarProyectil(float angulo, float velocidad);
    void controlarProyectil(float &angulo, float &velocidad, int tecla);
    void controlarProyectil2(float &angulo, float &velocidad, int tecla);

    void setTeclaPermitida(int tecla);
    void setTeclaNoPermitida(int tecla);

    int obtenerTeclaPermitida() const;
    int obtenerTeclaNoPermitida() const;
};

#endif // JUGADOR_H
