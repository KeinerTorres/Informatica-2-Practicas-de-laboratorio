#include "widget.h"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsItem>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    proyectil1(nullptr),
    angulo(-5),
    velocidad(300),
    angulo2(185),
    velocidad2(300),
    jugador1("Jugador 1", 0.0f, 330.0f),
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

    crearCastillo();

    // Proyectil jugador 1
    QPixmap proyectilSprite(":/images/Proyectil.png");
    proyectilSprite = proyectilSprite.scaled(70, 70, Qt::KeepAspectRatio);
    spriteProyectil = new QGraphicsPixmapItem(proyectilSprite);
    scene->addItem(spriteProyectil);
    spriteProyectil->setVisible(false);
    spriteProyectil->setZValue(1);

    // Jugador 1
    QPixmap jugadorSprite(":/images/Mortero.png");
    jugadorSprite = jugadorSprite.scaled(120, 120, Qt::KeepAspectRatio);
    spriteJugador = new QGraphicsPixmapItem(jugadorSprite);
    scene->addItem(spriteJugador);
    spriteJugador->setPos(jugador1.x, jugador1.y);
    spriteJugador->setZValue(0);

    // Jugador 2
    QPixmap jugadorSprite2(":/images/Mortero2.png");
    jugadorSprite2 = jugadorSprite2.scaled(120, 120, Qt::KeepAspectRatio);
    spriteJugador2 = new QGraphicsPixmapItem(jugadorSprite2);
    scene->addItem(spriteJugador2);
    spriteJugador2->setPos(jugador2.x, jugador2.y);
    spriteJugador2->setZValue(0);

    // Proyectil jugador 2
    QPixmap proyectilSprite2(":/images/Proyectil.png");
    proyectilSprite2 = proyectilSprite2.scaled(70, 70, Qt::KeepAspectRatio);
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

void Widget::crearCastillo() {
    //barras y muñeco
    vertical1 = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical2 = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    horizontal = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    horizontal2 = new QGraphicsPixmapItem(QPixmap(":/images/horizontal.png"));
    vertical3 = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    vertical4 = new QGraphicsPixmapItem(QPixmap(":/images/vertical.png"));
    muneco = new QGraphicsPixmapItem(QPixmap(":/images/Muneco.png"));
    muneco2 = new QGraphicsPixmapItem(QPixmap(":/images/Muneco.png"));

    // Escalar las paredes y muñeco
    vertical1->setTransform(QTransform::fromScale(0.3, 0.3));
    vertical2->setTransform(QTransform::fromScale(0.3, 0.3));
    horizontal->setTransform(QTransform::fromScale(0.3, 0.3));
    horizontal2->setTransform(QTransform::fromScale(0.3, 0.3));
    vertical3->setTransform(QTransform::fromScale(0.3, 0.3));
    vertical4->setTransform(QTransform::fromScale(0.3, 0.3));
    muneco->setTransform(QTransform::fromScale(0.3, 0.3));
    muneco2->setTransform(QTransform::fromScale(0.3, 0.3));



    vertical1->setPos(590, 400);   // Pared izquierda
    vertical2->setPos(420, 400);   // Pared derecha
    horizontal->setPos(505, 350);   // Pared horizontal


    vertical3->setPos(160, 400);   // Pared vertical 3
    vertical4->setPos(00, 400);    // Pared vertical 4
    horizontal2->setPos(75, 350);  // Pared horizontal 2

    scene->addItem(vertical1);
    scene->addItem(vertical2);
    scene->addItem(horizontal);
    scene->addItem(vertical3);
    scene->addItem(vertical4);
    scene->addItem(horizontal2);

    muneco->setPos(90, 440);
    scene->addItem(muneco);

    muneco2->setPos(500, 440);
    scene->addItem(muneco2);

    vidaV1 = 200;
    vidaV2 = 200;
    vidaH = 200;
    vidaV3 = 200;
    vidaV4 = 200;
    vidaH2 = 200;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    jugador1.controlarProyectil(angulo, velocidad, event->key());

    jugador2.controlarProyectil2(angulo2, velocidad2 , event->key());

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

void Widget::actualizarJuego() {
    if (proyectil1) {
        proyectil1->mover(0.016);
        proyectil1->colisionarConLimites(width(), height());
        spriteProyectil->setPos(proyectil1->x, proyectil1->y);

        if (spriteProyectil->collidesWithItem(vertical1)) {
            vidaV1 -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaV1 <= 0)
                vertical1->setVisible(false);
        }
        else if (spriteProyectil->collidesWithItem(vertical2)) {
            vidaV2 -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaV2 <= 0)
                vertical2->setVisible(false);
        }
        else if (spriteProyectil->collidesWithItem(horizontal)) {
            vidaH -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaH <= 0)
                horizontal->setVisible(false);
        }


        else if (spriteProyectil->collidesWithItem(vertical3)) {
            return;
        }
        else if (spriteProyectil->collidesWithItem(vertical4)) {
            return;
        }
        else if (spriteProyectil->collidesWithItem(horizontal2)) {
            return;
        }

        else if (proyectil1 && (proyectil1->x < 0 || proyectil1->x > width() ||
                                proyectil1->y < 0 || proyectil1->y > height())) {
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;
        }
    }

    if (proyectil2) {
        proyectil2->mover(0.016);
        proyectil2->colisionarConLimites(width(), height());
        spriteProyectil2->setPos(proyectil2->x, proyectil2->y);

        if (spriteProyectil2->collidesWithItem(vertical3)) {
            vidaV3 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaV3 <= 0)
                vertical3->setVisible(false);
        }
        else if (spriteProyectil2->collidesWithItem(vertical4)) {
            vidaV4 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaV4 <= 0)
                vertical4->setVisible(false);
        }
        else if (spriteProyectil2->collidesWithItem(horizontal2)) {
            vidaH2 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaH2 <= 0)
                horizontal2->setVisible(false);
        }

        else if (spriteProyectil2->collidesWithItem(vertical1)) {
            return;
        }
        else if (spriteProyectil2->collidesWithItem(vertical2)) {
            return;
        }
        else if (spriteProyectil2->collidesWithItem(horizontal)) {
            return;
        }

        else if (proyectil2 && (proyectil2->x < 0 || proyectil2->x > width() ||
                                proyectil2->y < 0 || proyectil2->y > height())) {
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;
        }
    }

    view->viewport()->update();
}
