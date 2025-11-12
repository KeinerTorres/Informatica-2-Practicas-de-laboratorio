#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    double componenteX;
    double componenteY;

    Vector2D(double x, double y);
    Vector2D();

    Vector2D sumar(const Vector2D &otro) const;
    Vector2D restar(const Vector2D &otro) const;
    Vector2D multiplicarPorEscalar(double escalar) const;

    double obtenerLongitud() const;
    Vector2D obtenerNormalizado() const;
    double productoPunto(const Vector2D &otro) const;
};

#endif // VECTOR2D_H
