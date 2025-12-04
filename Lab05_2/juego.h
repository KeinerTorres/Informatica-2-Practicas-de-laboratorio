#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "Castillo.h"
#include "Proyectil.h"

class Juego {
public:
    Juego();
    ~Juego();

    void iniciarJuego();

    void cambiarTurno();

    bool verificarVictoria();

    void calcularDanio(QGraphicsItem *pared, float velocidadProyectil, bool esJugador1);

    Jugador* obtenerJugador1();
    Jugador* obtenerJugador2();
    Castillo* obtenerCastillo1();
    Castillo* obtenerCastillo2();
    bool esTurnoJugador1() const;
    bool puedeDisparar() const;

private:
    bool turnoJugador1;
    bool disparoJugador1;
    bool disparoJugador2;
    Jugador *jugador1;
    Jugador *jugador2;
    Castillo *castillo1;
    Castillo *castillo2;
};

#endif // JUEGO_H
