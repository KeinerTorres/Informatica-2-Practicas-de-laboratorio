#include "Jugador.h"
#include <QKeyEvent>

Jugador::Jugador(const std::string &nombreJugador, float posX, float posY)
    : nombre(nombreJugador),
    proyectilesLanzados(0),
    x(posX),
    y(posY)
{
}

Proyectil* Jugador::lanzarProyectil(float angulo, float velocidad)
{
    proyectilesLanzados++;
    return new Proyectil(x, y, 1.0f, angulo, velocidad);
}

void Jugador::controlarProyectil(float &angulo, float &velocidad, int tecla)
{
    if (tecla == Qt::Key_Up)
        velocidad += 1;

    else if (tecla == Qt::Key_Down && velocidad > 1)
        velocidad -= 1;

    else if (tecla == Qt::Key_Left) {
        angulo -= 5;
        if (angulo < 0) angulo = 360;
    }
    else if (tecla == Qt::Key_Right) {
        angulo += 5;
        if (angulo >= 360) angulo = 0;
    }
}

void Jugador::controlarProyectil2(float &angulo, float &velocidad, int tecla)
{
    if (tecla == Qt::Key_W)
        velocidad += 1;

    else if (tecla == Qt::Key_S && velocidad > 1)
        velocidad -= 1;

    else if (tecla == Qt::Key_A) {
        angulo -= 5;
        if (angulo < 0) angulo = 360;
    }
    else if (tecla == Qt::Key_D) {
        angulo += 5;
        if (angulo >= 360) angulo = 0;
    }
}
