#ifndef CASTILLO_H
#define CASTILLO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>

class Castillo : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Castillo(QObject *parent = nullptr);


    int vidaV1;
    int vidaV2;
    int vidaH;
    int vidaV3;
    int vidaV4;
    int vidaH2;

    void recibirDanio(QGraphicsItem *pared, int cantidad, bool esJugador1, float velocidadProyectil);
    void colisionarConProyectil(QGraphicsItem *proyectil, bool esJugador1);

signals:
    void finDelJuego();

private:
    QGraphicsPixmapItem *horizontal;
    QGraphicsPixmapItem *horizontal2;
    QGraphicsPixmapItem *vertical1;
    QGraphicsPixmapItem *vertical2;
    QGraphicsPixmapItem *vertical3;
    QGraphicsPixmapItem *vertical4;
    QGraphicsPixmapItem *muneco;
    QGraphicsPixmapItem *muneco2;
};

#endif // CASTILLO_H
