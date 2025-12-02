#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include "Proyectil.h"

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

    QGraphicsScene *scene;
    QGraphicsView *view;


    QGraphicsPixmapItem *spriteFondo;
    QGraphicsPixmapItem *spriteProyectil;

    QTimer *timer;
    Proyectil* proyectil1;

    void actualizarJuego();
};

#endif // WIDGET_H
