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
    velocidad(300)
{
    setWindowTitle("Juego Interactivo");
    resize(800, 600);

    // Crear la escena
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(800, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Cargar el fondo
    QPixmap fondo(":/images/background.png");
    fondo = fondo.scaled(800, 600, Qt::KeepAspectRatioByExpanding);
    spriteFondo = scene->addPixmap(fondo);
    spriteFondo->setPos(0, 0);

    QPixmap proyectilSprite(":/images/Proyectil.png");
    proyectilSprite = proyectilSprite.scaled(50, 50, Qt::KeepAspectRatio);

    spriteProyectil = new QGraphicsPixmapItem(proyectilSprite);
    scene->addItem(spriteProyectil);
    spriteProyectil->setVisible(false);


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
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        velocidad += 1;
    }
    if (event->key() == Qt::Key_Down) {
        if (velocidad > 1) velocidad -= 1;
    }

    if (event->key() == Qt::Key_Left) {
        angulo -= 5;
        if (angulo < 0) angulo = 360;
    }
    if (event->key() == Qt::Key_Right) {
        angulo += 5;
        if (angulo >= 360) angulo = 0;
    }

    if (event->key() == Qt::Key_Space) {
        if (!proyectil1) {
            proyectil1 = new Proyectil(80, 330, 1, angulo, velocidad);
            spriteProyectil->setVisible(true);
            spriteProyectil->setPos(80, 330);
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

    update();
}
