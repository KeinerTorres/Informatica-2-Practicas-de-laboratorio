#include "Juego.h"

Juego::Juego()
    : turnoJugador1(true),
    disparoJugador1(false),
    disparoJugador2(false),
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
    if (turnoJugador1) {
        disparoJugador1 = false;
    } else {
        disparoJugador2 = false;
    }

    turnoJugador1 = !turnoJugador1;
}

bool Juego::verificarVictoria() {

    if (castillo1->vidaH <= 0 && castillo1->vidaV1 <= 0 && castillo1->vidaV2 <= 0 && castillo1->vidaH2 <= 0 && castillo1->vidaV3 <= 0 && castillo1->vidaV4 <= 0) {
        return true;
    }
    if (castillo2->vidaH <= 0 && castillo2->vidaV1 <= 0 && castillo2->vidaV2 <= 0 && castillo2->vidaH2 <= 0 && castillo2->vidaV3 <= 0 && castillo2->vidaV4 <= 0) {
        return true;
    }
    return false;
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

bool Juego::puedeDisparar() const {
    if (turnoJugador1 && !disparoJugador1) {
        return true;
    } else if (!turnoJugador1 && !disparoJugador2) {
        return true;
    }
    return false;
}
