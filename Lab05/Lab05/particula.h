#ifndef PARTICULA_H
#define PARTICULA_H

#include "Vector2D.h"

class Particula
{
private:
    int identificador;
    Vector2D posicion;
    Vector2D velocidad;
    double masa;
    double radio;
    bool activa;

public:
    Particula(int id,
              const Vector2D &posicionInicial,
              const Vector2D &velocidadInicial,
              double masaInicial,
              double radioInicial);

    void actualizar(double deltaTiempo);

    int obtenerIdentificador() const;
    const Vector2D &obtenerPosicion() const;
    const Vector2D &obtenerVelocidad() const;
    double obtenerMasa() const;
    double obtenerRadio() const;
    bool estaActiva() const;

    void establecerPosicion(const Vector2D &nuevaPosicion);
    void establecerVelocidad(const Vector2D &nuevaVelocidad);
    void establecerMasa(double nuevaMasa);
    void establecerRadio(double nuevoRadio);
    void establecerActiva(bool estado);

};

#endif // PARTICULA_H
