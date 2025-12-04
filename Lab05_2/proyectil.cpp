#include "Proyectil.h"
#include <cmath>


Proyectil::Proyectil(float _x, float _y, float _masa, float _angulo, float _velocidad)
    : x(_x), y(_y), masa(_masa), angulo(_angulo), velocidad(_velocidad), gravedad(-2.0) {
    angulo = angulo * M_PI / 180.0;
    v_x = velocidad * cos(angulo);
    v_y = velocidad * sin(angulo);
}


void Proyectil::mover(float dt) {
    x += v_x * dt;
    y += v_y * dt;

    v_y -= gravedad;

    if (y > 600) {
        y = 600;
        v_y = 0;
    }
}

void Proyectil::colisionarConLimites(float anchoEscenario, float altoEscenario) {
    if (x <= 0 || x >= anchoEscenario) {
        v_x = -v_x;
    }
    if (y <= 0 || y >= altoEscenario) {
        v_y = -v_y;
    }
}

float Proyectil::obtenerVelocidad() const
{
    return velocidad;
}
