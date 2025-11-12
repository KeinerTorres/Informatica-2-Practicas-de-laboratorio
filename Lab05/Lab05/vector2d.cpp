#include "Vector2D.h"
#include <cmath>
using namespace std;

Vector2D::Vector2D(double x, double y)
    : componenteX(x), componenteY(y)
{
}

Vector2D::Vector2D()
    : componenteX(0.0), componenteY(0.0)
{
}

Vector2D Vector2D::sumar(const Vector2D &otro) const
{
    return Vector2D(componenteX + otro.componenteX,
                    componenteY + otro.componenteY);
}

Vector2D Vector2D::restar(const Vector2D &otro) const
{
    return Vector2D(componenteX - otro.componenteX,
                    componenteY - otro.componenteY);
}

Vector2D Vector2D::multiplicarPorEscalar(double escalar) const
{
    return Vector2D(componenteX * escalar,
                    componenteY * escalar);
}

double Vector2D::obtenerLongitud() const
{
    return sqrt(componenteX * componenteX +
                componenteY * componenteY);
}

Vector2D Vector2D::obtenerNormalizado() const
{
    double longitud = obtenerLongitud();
    if (longitud == 0.0)
    {
        return Vector2D(0.0, 0.0);
    }
    return Vector2D(componenteX / longitud,
                    componenteY / longitud);
}

double Vector2D::productoPunto(const Vector2D &otro) const
{
    return componenteX * otro.componenteX +
           componenteY * otro.componenteY;
}
