#include "Jugador.h"
#include <QKeyEvent>

Jugador::Jugador(const std::string &nombreJugador, float posX, float posY)
    : nombre(nombreJugador),
    proyectilesLanzados(0),
    x(posX),
    y(posY),
    teclaPermitida(Qt::Key_Space),
    teclaNoPermitida(Qt::Key_K)
{
}

Proyectil* Jugador::lanzarProyectil(float angulo, float velocidad)
{
    proyectilesLanzados++;
    return new Proyectil(x, y, 3.0f, angulo, velocidad);
}

void Jugador::setTeclaPermitida(int tecla) {
    teclaPermitida = tecla;
}

void Jugador::setTeclaNoPermitida(int tecla) {
    teclaNoPermitida = tecla;
}

int Jugador::obtenerTeclaPermitida() const {
    return teclaPermitida;
}

int Jugador::obtenerTeclaNoPermitida() const {
    return teclaNoPermitida;
}

void Jugador::controlarProyectil(float &angulo, float &velocidad, int tecla)
{

        if (tecla == Qt::Key_Up)
            velocidad += 10;

        else if (tecla == Qt::Key_Down && velocidad > 1)
            velocidad -= 10;

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
            velocidad += 10;

        else if (tecla == Qt::Key_S && velocidad > 1)
            velocidad -= 10;

        else if (tecla == Qt::Key_A) {
            angulo -= 10;
            if (angulo < 0) angulo = 360;
        }
        else if (tecla == Qt::Key_D) {
            angulo += 10;
            if (angulo >= 360) angulo = 0;
        }
}
