#ifndef CAJA_H
#define CAJA_H

#include "Particula.h"

class Caja
{
private:
    double limiteIzquierdo;
    double limiteDerecho;
    double limiteInferior;
    double limiteSuperior;

public:
    Caja(double xMinimo,
         double xMaximo,
         double yMinimo,
         double yMaximo);

    void manejarColisionConParticula(Particula &particula) const;
};

#endif // CAJA_H
