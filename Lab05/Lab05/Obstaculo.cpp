#include "Obstaculo.h"
#include <algorithm>
#include <cmath>
using namespace std;

double Obstaculo::limitarValor(double valor,
                               double minimo,
                               double maximo)
{
    return max(minimo, min(valor, maximo));
}

Obstaculo::Obstaculo(const Vector2D &centroObstaculo,
                     double anchoObstaculo,
                     double altoObstaculo)
    : centro(centroObstaculo),
    ancho(anchoObstaculo),
    alto(altoObstaculo)
{
}

const Vector2D &Obstaculo::obtenerCentro() const
{
    return centro;
}

double Obstaculo::obtenerAncho() const
{
    return ancho;
}

double Obstaculo::obtenerAlto() const
{
    return alto;
}

bool Obstaculo::verificarColisionConParticula(const Particula &particula,
                                              Vector2D &normalColision) const
{
    if (!particula.estaActiva())
        return false;

    Vector2D posicionParticula = particula.obtenerPosicion();
    double radioParticula = particula.obtenerRadio();

    double bordeIzquierdo = centro.componenteX - ancho / 2.0;
    double bordeDerecho = centro.componenteX + ancho / 2.0;
    double bordeInferior = centro.componenteY - alto / 2.0;
    double bordeSuperior = centro.componenteY + alto / 2.0;

    double puntoMasCercanoX = limitarValor(posicionParticula.componenteX,
                                           bordeIzquierdo,
                                           bordeDerecho);
    double puntoMasCercanoY = limitarValor(posicionParticula.componenteY,
                                           bordeInferior,
                                           bordeSuperior);

    double diferenciaX = posicionParticula.componenteX - puntoMasCercanoX;
    double diferenciaY = posicionParticula.componenteY - puntoMasCercanoY;
    double distanciaCuadrada = diferenciaX * diferenciaX +
                               diferenciaY * diferenciaY;

    if (distanciaCuadrada > radioParticula * radioParticula)
        return false;

    double distanciaIzquierda = abs(posicionParticula.componenteX - bordeIzquierdo);
    double distanciaDerecha   = abs(posicionParticula.componenteX - bordeDerecho);
    double distanciaInferior  = abs(posicionParticula.componenteY - bordeInferior);
    double distanciaSuperior  = abs(posicionParticula.componenteY - bordeSuperior);

    double distanciaMinima = distanciaIzquierda;
    normalColision = Vector2D(-1.0, 0.0);

    if (distanciaDerecha < distanciaMinima)
    {
        distanciaMinima = distanciaDerecha;
        normalColision = Vector2D(1.0, 0.0);
    }
    if (distanciaInferior < distanciaMinima)
    {
        distanciaMinima = distanciaInferior;
        normalColision = Vector2D(0.0, -1.0);
    }
    if (distanciaSuperior < distanciaMinima)
    {
        distanciaMinima = distanciaSuperior;
        normalColision = Vector2D(0.0, 1.0);
    }

    return true;
}
