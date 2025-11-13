#include "Caja.h"
using namespace std;

Caja::Caja(double xMinimo,
           double xMaximo,
           double yMinimo,
           double yMaximo)
    : limiteIzquierdo(xMinimo),
    limiteDerecho(xMaximo),
    limiteInferior(yMinimo),
    limiteSuperior(yMaximo)
{
}

void Caja::manejarColisionConParticula(Particula &particula) const
{
    if (!particula.estaActiva())
        return;

    Vector2D posicion = particula.obtenerPosicion();
    Vector2D velocidad = particula.obtenerVelocidad();
    double radio = particula.obtenerRadio();

    bool huboColision = false;

    if (posicion.componenteX - radio < limiteIzquierdo)
    {
        posicion.componenteX = limiteIzquierdo + radio;
        velocidad.componenteX *= -1.0;
        huboColision = true;
    }
    else if (posicion.componenteX + radio > limiteDerecho)
    {
        posicion.componenteX = limiteDerecho - radio;
        velocidad.componenteX *= -1.0;
        huboColision = true;
    }

    if (posicion.componenteY - radio < limiteInferior)
    {
        posicion.componenteY = limiteInferior + radio;
        velocidad.componenteY *= -1.0;
        huboColision = true;
    }
    else if (posicion.componenteY + radio > limiteSuperior)
    {
        posicion.componenteY = limiteSuperior - radio;
        velocidad.componenteY *= -1.0;
        huboColision = true;
    }

    if (huboColision)
    {
        particula.establecerPosicion(posicion);
        particula.establecerVelocidad(velocidad);
    }
}
