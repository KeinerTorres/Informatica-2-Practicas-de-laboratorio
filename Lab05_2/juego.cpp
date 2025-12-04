#include "Juego.h"

Juego::Juego()
    : turnoJugador1(true),
    turnoJugador2(false),
    proyectil1(nullptr),
    proyectil2(nullptr),
    jugador1(new Jugador("Jugador 1", 0.0f, 330.0f)),
    jugador2(new Jugador("Jugador 2", 700.0f, 330.0f)),
    castillo1(new Castillo()),
    castillo2(new Castillo()) {}

Juego::~Juego() {
    delete jugador1;
    delete jugador2;
    delete castillo1;
    delete castillo2;
}

void Juego::iniciarJuego() {
    castillo1->setPos(100, 300);
    castillo2->setPos(600, 300);
}

void Juego::cambiarTurno() {
    turnoJugador1 = !turnoJugador1;
    turnoJugador2 = !turnoJugador2;
    bloquearTeclas();
}

bool Juego::verificarVictoria() {
    if (todasLasBarrerasDestruidas(true) && castillo2->obtenerMuneco2()->collidesWithItem(proyectil1)) {
        return true;
    }

    if (todasLasBarrerasDestruidas(false) && castillo1->obtenerMuneco1()->collidesWithItem(proyectil2)) {
        return true;
    }

    return false;
}


bool Juego::todasLasBarrerasDestruidas(bool esJugador1) {
    if (esJugador1) {
        return castillo2->vidaH <= 0 && castillo2->vidaV1 <= 0 && castillo2->vidaV2 <= 0 &&
               castillo2->vidaH2 <= 0 && castillo2->vidaV3 <= 0 && castillo2->vidaV4 <= 0;
    } else {
        return castillo1->vidaH <= 0 && castillo1->vidaV1 <= 0 && castillo1->vidaV2 <= 0 &&
               castillo1->vidaH2 <= 0 && castillo1->vidaV3 <= 0 && castillo1->vidaV4 <= 0;
    }
}

void Juego::calcularDanio(QGraphicsItem *pared, float velocidadProyectil, bool esJugador1) {
    if (esJugador1) {
        castillo2->recibirDanio(pared, 100, esJugador1, velocidadProyectil);
    } else {
        castillo1->recibirDanio(pared, 100, esJugador1, velocidadProyectil);
    }
}

Jugador* Juego::obtenerJugador1() {
    return jugador1;
}

Jugador* Juego::obtenerJugador2() {
    return jugador2;
}

Castillo* Juego::obtenerCastillo1() {
    return castillo1;
}

Castillo* Juego::obtenerCastillo2() {
    return castillo2;
}

bool Juego::esTurnoJugador1() const {
    return turnoJugador1;
}

bool Juego::esTurnoJugador2() const {
    return turnoJugador2;
}

void Juego::bloquearTeclas() {
    if (turnoJugador1) {
        jugador1->setTeclaPermitida(Qt::Key_Space);
        jugador2->setTeclaNoPermitida(Qt::Key_K);
    } else if (turnoJugador2) {
        jugador2->setTeclaPermitida(Qt::Key_K);
        jugador1->setTeclaNoPermitida(Qt::Key_Space);
    }
}
