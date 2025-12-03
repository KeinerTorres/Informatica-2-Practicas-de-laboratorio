#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include "Proyectil.h"
#include "Jugador.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:

    float angulo;
    float velocidad;

    float angulo2;
    float velocidad2;

    QGraphicsScene *scene;
    QGraphicsView *view;


    QGraphicsPixmapItem *spriteFondo;
    QGraphicsPixmapItem *spriteProyectil;
    QGraphicsPixmapItem *spriteJugador;

    QGraphicsPixmapItem *spriteProyectil2;
    QGraphicsPixmapItem *spriteJugador2;

    QTimer *timer;
    Proyectil* proyectil1;
    Jugador jugador1;

    Proyectil* proyectil2;
    Jugador jugador2;

    void actualizarJuego();
};

#endif // WIDGET_H
