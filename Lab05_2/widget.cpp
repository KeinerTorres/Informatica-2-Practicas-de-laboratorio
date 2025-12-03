#include "widget.h"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    proyectil1(nullptr),
    angulo(-5),
    angulo2(185),
    velocidad2(300),
    velocidad(300),
    jugador1("Jugador 1", 80.0f, 330.0f),
    proyectil2(nullptr),
    jugador2("Jugador 2", 700.0f, 330.0f)
{
    setWindowTitle("Juego Interactivo");
    resize(800, 600);


    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    // Crear la escena
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFocusPolicy(Qt::NoFocus);

    // Cargar el fondo
    QPixmap fondo(":/images/background.png");
    fondo = fondo.scaled(800, 600, Qt::KeepAspectRatioByExpanding);
    spriteFondo = scene->addPixmap(fondo);
    spriteFondo->setPos(0, 0);
    spriteFondo->setZValue(-1);

    QPixmap proyectilSprite(":/images/Proyectil.png");
    proyectilSprite = proyectilSprite.scaled(50, 50, Qt::KeepAspectRatio);
    spriteProyectil = new QGraphicsPixmapItem(proyectilSprite);
    scene->addItem(spriteProyectil);
    spriteProyectil->setVisible(false);
    spriteProyectil->setZValue(1);


    QPixmap jugadorSprite(":/images/Mortero.png");
    jugadorSprite = jugadorSprite.scaled(70, 70, Qt::KeepAspectRatio);
    spriteJugador = new QGraphicsPixmapItem(jugadorSprite);
    scene->addItem(spriteJugador);
    spriteJugador->setPos(jugador1.x, jugador1.y);
    spriteJugador->setZValue(0);

    QPixmap jugadorSprite2(":/images/Mortero2.png");
    jugadorSprite2 = jugadorSprite2.scaled(70, 70, Qt::KeepAspectRatio);
    spriteJugador2 = new QGraphicsPixmapItem(jugadorSprite2);
    scene->addItem(spriteJugador2);
    spriteJugador2->setPos(jugador2.x, jugador2.y);
    spriteJugador2->setZValue(0);


    QPixmap proyectilSprite2(":/images/Proyectil.png");
    proyectilSprite2 = proyectilSprite2.scaled(50, 50, Qt::KeepAspectRatio);
    spriteProyectil2 = new QGraphicsPixmapItem(proyectilSprite2);
    scene->addItem(spriteProyectil2);
    spriteProyectil2->setVisible(false);
    spriteProyectil2->setZValue(1);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::actualizarJuego);
    timer->start(16);
}

Widget::~Widget()
{
    delete timer;
    if (proyectil1) {
        delete proyectil1;
    }
    if (proyectil2) {
        delete proyectil2;
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{

    jugador1.controlarProyectil(angulo, velocidad, event->key());

    jugador2.controlarProyectil2(angulo2, velocidad2, event->key());

    if (event->key() == Qt::Key_Space) {
        if (!proyectil1) {
            proyectil1 = jugador1.lanzarProyectil(angulo, velocidad);
            spriteProyectil->setVisible(true);
            spriteProyectil->setPos(jugador1.x, jugador1.y);
            spriteProyectil->setZValue(1);
        }
    }

    if (event->key() == Qt::Key_K) {
        if (!proyectil2) {
            proyectil2 = jugador2.lanzarProyectil(angulo2, velocidad2);
            spriteProyectil2->setVisible(true);
            spriteProyectil2->setPos(jugador2.x, jugador2.y);
            spriteProyectil2->setZValue(1);
        }
    }
}

void Widget::actualizarJuego()
{
    if (proyectil1) {
        proyectil1->mover(0.016);
        proyectil1->colisionarConLimites(width(), height());

        spriteProyectil->setPos(proyectil1->x, proyectil1->y);

        if (proyectil1->x < 0 || proyectil1->x > width() || proyectil1->y < 0 || proyectil1->y > height()) {
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;
        }
    }

    if (proyectil2) {
        proyectil2->mover(0.016);
        proyectil2->colisionarConLimites(width(), height());

        spriteProyectil2->setPos(proyectil2->x, proyectil2->y);

        if (proyectil2->x < 0 || proyectil2->x > width() ||
            proyectil2->y < 0 || proyectil2->y > height()) {
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;
        }
    }

    view->viewport()->update();
}
