#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include "Proyectil.h"
#include "Jugador.h"
#include "castillo.h"
#include "Juego.h"

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

    QGraphicsPixmapItem *vertical1;
    QGraphicsPixmapItem *vertical2;
    QGraphicsPixmapItem *horizontal;
    QGraphicsPixmapItem *horizontal2;
    QGraphicsPixmapItem *vertical3;
    QGraphicsPixmapItem *vertical4;
    QGraphicsPixmapItem *muneco;
    QGraphicsPixmapItem *muneco2;
    QGraphicsPixmapItem *plataforma1;
    QGraphicsPixmapItem *plataforma2;

    int vidaV1;
    int vidaV2;
    int vidaH;
    int vidaV3;
    int vidaV4;
    int vidaH2;
    int vidaMuñeco1;
    int vidaMuñeco2;

    bool turnoJugador1;
    bool turnoJugador2;

    Juego juego;

    QLabel *mensajeVictoria;

    void crearCastillo();
    void crearPlataformas();

    void actualizarJuego();
    void mostrarMensajeVictoria(const QString &mensaje);
};

#endif // WIDGET_H
