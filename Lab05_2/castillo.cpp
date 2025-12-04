#include "castillo.h"
#include "proyectil.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>

Castillo::Castillo(QObject *parent)
    : QObject(parent),
    QGraphicsItemGroup(),
    horizontal(nullptr),
    horizontal2(nullptr),
    vertical1(nullptr),
    vertical2(nullptr),
    vertical3(nullptr),
    vertical4(nullptr),
    muneco(nullptr),
    vidaV1(200),
    vidaV2(200),
    vidaH(200),
    vidaV3(200),
    vidaV4(200),
    vidaH2(200),
    vidaMuñeco1(50),
    vidaMuñeco2(50)
{
    horizontal = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    horizontal2 = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    vertical1   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical2   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical3   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical4   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    muneco      = new QGraphicsPixmapItem(QPixmap(":/images/Muneco.png"));
    muneco2     = new QGraphicsPixmapItem(QPixmap(":/images/Muneco.png"));

    horizontal->setPos(75, 350);
    vertical1->setPos(160, 400);   // Pared izquierda del jugador 1
    vertical2->setPos(-10, 400);   // Pared derecha del jugador 1
    horizontal2->setPos(475, 350); // Pared horizontal 2 del jugador 2
    vertical3->setPos(550, 400);   // Pared izquierda del jugador 2
    vertical4->setPos(600, 400);   // Pared derecha del jugador 2
    muneco->setPos(85, 270);
    muneco2->setPos(585, 270);

    addToGroup(horizontal);
    addToGroup(vertical1);
    addToGroup(vertical2);
    addToGroup(horizontal2);
    addToGroup(vertical3);
    addToGroup(vertical4);
    addToGroup(muneco);
    addToGroup(muneco2);
}

void Castillo::recibirDanio(QGraphicsItem *pared, int cantidad, bool esJugador1, float velocidadProyectil) {

    float dano = cantidad * velocidadProyectil;

    if (pared == horizontal) {
        if (!esJugador1) {
            vidaH -= dano;
            if (vidaH <= 0) {
                delete horizontal;
            }
        }
    } else if (pared == vertical1) {
        if (esJugador1) return;  // Para que el jugador 1 no le hace daño a sus propias paredes
        vidaV1 -= dano;
        if (vidaV1 <= 0) {
            delete vertical1;
        }
    } else if (pared == vertical2) {
        if (esJugador1) return;
        vidaV2 -= dano;
        if (vidaV2 <= 0) {
            delete vertical2;
        }
    } else if (pared == horizontal2) {
        if (esJugador1) {
            vidaH2 -= dano;
            if (vidaH2 <= 0) {
                delete horizontal2;
            }
        }
    } else if (pared == vertical3) {
        if (esJugador1) {
            vidaV3 -= dano;
            if (vidaV3 <= 0) {
                delete vertical3;
            }
        }
    } else if (pared == vertical4) {
        if (esJugador1) {
            vidaV4 -= dano;
            if (vidaV4 <= 0) {
                delete vertical4;
            }
        }
    } else {
        return;
    }

    if (vidaH <= 0 && vidaV1 <= 0 && vidaV2 <= 0 && vidaH2 <= 0 && vidaV3 <= 0 && vidaV4 <= 0) {
        emit finDelJuego();
    }
}

void Castillo::colisionarConProyectil(QGraphicsItem *proyectil, bool esJugador1) {

    Proyectil* proyectilItem = dynamic_cast<Proyectil*>(proyectil);

    if (proyectilItem) {
        float velocidadProyectil = proyectilItem->obtenerVelocidad();

        if (proyectil->collidesWithItem(vertical1)) {
            recibirDanio(vertical1, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(vertical2)) {
            recibirDanio(vertical2, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(horizontal)) {
            recibirDanio(horizontal, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(horizontal2)) {
            recibirDanio(horizontal2, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(vertical3)) {
            recibirDanio(vertical3, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(vertical4)) {
            recibirDanio(vertical4, 10, esJugador1, velocidadProyectil);
        }
        if (proyectil->collidesWithItem(muneco)) {
            emit finDelJuego();
        }
        if (proyectil->collidesWithItem(muneco2)) {
            emit finDelJuego();
        }

        if (proyectil->collidesWithItem(muneco)) {
            vidaMuñeco1 -= velocidadProyectil;
            if (vidaMuñeco1 <= 0) {
                emit finDelJuego();
                muneco->setVisible(false);
                delete muneco;
                muneco = nullptr;
            }
        }


        if (proyectil->collidesWithItem(muneco2)) {
            vidaMuñeco2 -= velocidadProyectil;
            if (vidaMuñeco2 <= 0) {
                emit finDelJuego();
                muneco2->setVisible(false);
                delete muneco2;
                muneco2 = nullptr;
            }
        }
    }
}
