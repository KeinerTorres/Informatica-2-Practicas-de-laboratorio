#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Particula.h"

class Obstaculo
{
private:
    Vector2D centro;
    double ancho;
    double alto;

    static double limitarValor(double valor,
                               double minimo,
                               double maximo);

public:
    Obstaculo(const Vector2D &centroObstaculo,
              double anchoObstaculo,
              double altoObstaculo);

    const Vector2D &obtenerCentro() const;
    double obtenerAncho() const;
    double obtenerAlto() const;

    bool verificarColisionConParticula(const Particula &particula,
                                       Vector2D &normalColision) const;
};

#endif // OBSTACULO_H
