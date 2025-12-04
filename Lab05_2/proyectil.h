#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>

class Proyectil : public QGraphicsPixmapItem {
public:
    float x, y;
    float v_x, v_y;
    float masa;
    float angulo;
    float velocidad;
    float gravedad;

    Proyectil(float _x, float _y, float _masa, float _angulo, float _velocidad);

    void mover(float dt);
    void colisionarConLimites(float anchoEscenario, float altoEscenario);

    float obtenerVelocidad() const;
};

#endif // PROYECTIL_H
