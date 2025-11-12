#include "Particula.h"
using namespace std;

Particula::Particula(int id,
                     const Vector2D &posicionInicial,
                     const Vector2D &velocidadInicial,
                     double masaInicial,
                     double radioInicial)
    : identificador(id),
    posicion(posicionInicial),
    velocidad(velocidadInicial),
    masa(masaInicial),
    radio(radioInicial),
    activa(true)
{
}

void Particula::actualizar(double deltaTiempo)
{
    if (!activa)
        return;

    posicion = posicion.sumar(velocidad.multiplicarPorEscalar(deltaTiempo));
}

int Particula::obtenerIdentificador() const
{
    return identificador;
}

const Vector2D &Particula::obtenerPosicion() const
{
    return posicion;
}

const Vector2D &Particula::obtenerVelocidad() const
{
    return velocidad;
}

double Particula::obtenerMasa() const
{
    return masa;
}

double Particula::obtenerRadio() const
{
    return radio;
}

bool Particula::estaActiva() const
{
    return activa;
}

