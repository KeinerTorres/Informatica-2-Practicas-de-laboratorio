#include "castillo.h"
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
    vidaH2(200)
{
    horizontal = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    horizontal2 = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    vertical1   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical2   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical3   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical4   = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    muneco      = new QGraphicsPixmapItem(QPixmap(":/images/Muneco.png"));

    horizontal->setPos(75, 350);
    vertical1->setPos(160, 400);   // Pared izquierda del jugador 1
    vertical2->setPos(-10, 400);   // Pared derecha del jugador 1
    horizontal2->setPos(475, 350); // Pared horizontal 2 del jugador 2
    vertical3->setPos(550, 400);   // Pared izquierda del jugador 2
    vertical4->setPos(600, 400);   // Pared derecha del jugador 2
    muneco->setPos(85, 270);

    addToGroup(horizontal);
    addToGroup(vertical1);
    addToGroup(vertical2);
    addToGroup(horizontal2);
    addToGroup(vertical3);
    addToGroup(vertical4);
    addToGroup(muneco);
}

void Castillo::recibirDanio(QGraphicsItem *pared, int cantidad, bool esJugador1) {
    if (pared == horizontal) {
        if (!esJugador1) {
            vidaH -= cantidad;
            if (vidaH <= 0) {
                horizontal->setVisible(false);
            }
        }
    } else if (pared == vertical1) {
        if (esJugador1) return;  // Para que el jugador 1 no le hace daño a sus propias paredes
        vidaV1 -= cantidad;
        if (vidaV1 <= 0) {
            vertical1->setVisible(false);
        }
    } else if (pared == vertical2) {
        if (esJugador1) return;
        vidaV2 -= cantidad;
        if (vidaV2 <= 0) {
            vertical2->setVisible(false);
        }
    } else if (pared == horizontal2) {
        if (esJugador1) {
            vidaH2 -= cantidad;
            if (vidaH2 <= 0) {
                horizontal2->setVisible(false);
            }
        }
    } else if (pared == vertical3) {
        if (esJugador1) {
            vidaV3 -= cantidad;
            if (vidaV3 <= 0) {
                vertical3->setVisible(false);
            }
        }
    } else if (pared == vertical4) {
        if (esJugador1) {
            vidaV4 -= cantidad;
            if (vidaV4 <= 0) {
                vertical4->setVisible(false);
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
    if (proyectil->collidesWithItem(vertical1)) {
        recibirDanio(vertical1, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(vertical2)) {
        recibirDanio(vertical2, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(horizontal)) {
        recibirDanio(horizontal, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(horizontal2)) {
        recibirDanio(horizontal2, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(vertical3)) {
        recibirDanio(vertical3, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(vertical4)) {
        recibirDanio(vertical4, 10, esJugador1);
    }
    if (proyectil->collidesWithItem(muneco)) {
        emit finDelJuego();
    }
    if (proyectil->collidesWithItem(muneco2)) {
        emit finDelJuego();
    }
}
