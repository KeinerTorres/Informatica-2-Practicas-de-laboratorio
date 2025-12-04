#include "widget.h"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsItem>
#include <QDebug>
#include "Juego.h"
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    proyectil1(nullptr),
    angulo(-5),
    velocidad(300),
    angulo2(240),
    velocidad2(300),
    jugador1("Jugador 1", -1.0f, 290.0f),
    proyectil2(nullptr),
    jugador2("Jugador 2", 700.0f, 290.0f),
    turnoJugador1(true),
    turnoJugador2(false),
    vidaMuñeco1(50),
    vidaMuñeco2(50),
    plataforma1(nullptr),
    plataforma2(nullptr),
    juego()
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
    crearPlataformas();

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

    mensajeVictoria = new QLabel(this);
    mensajeVictoria->setAlignment(Qt::AlignCenter);
    mensajeVictoria->setStyleSheet("font-size: 30px; color: white;");
    mensajeVictoria->setGeometry(0, 0, 800, 300);
    mensajeVictoria->hide();
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

void Widget::crearPlataformas() {
    // Plataforma 1
    QPixmap plataformaSprite(":/images/Plataforma.png");
    plataformaSprite = plataformaSprite.scaled(150, 100, Qt::KeepAspectRatio); // Ajusta el tamaño
    plataforma1 = new QGraphicsPixmapItem(plataformaSprite);
    scene->addItem(plataforma1);
    plataforma1->setPos(-27, 295);
    plataforma1->setZValue(0);

    // Plataforma 2
    plataforma2 = new QGraphicsPixmapItem(plataformaSprite);
    scene->addItem(plataforma2);
    plataforma2->setPos(677, 295);
    plataforma2->setZValue(0);
}


void Widget::mostrarMensajeVictoria(const QString &mensaje)
{
    mensajeVictoria->setText(mensaje);
    mensajeVictoria->show();
    timer->stop();
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

void Widget::keyPressEvent(QKeyEvent *event) {

    if (juego.esTurnoJugador1()) {
        jugador1.controlarProyectil(angulo, velocidad, event->key());
    } else if (juego.esTurnoJugador2()) {
        jugador2.controlarProyectil2(angulo2, velocidad2, event->key());
    }

    if (juego.esTurnoJugador1() && event->key() == Qt::Key_Space) {
        if (!proyectil1) {
            proyectil1 = jugador1.lanzarProyectil(angulo, velocidad);
            spriteProyectil->setVisible(true);
            spriteProyectil->setPos(jugador1.x, jugador1.y);
            spriteProyectil->setZValue(1);
            juego.cambiarTurno();
        }
    }

    else if (juego.esTurnoJugador2() && event->key() == Qt::Key_K) {
        if (!proyectil2) {
            proyectil2 = jugador2.lanzarProyectil(angulo2, velocidad2);
            spriteProyectil2->setVisible(true);
            spriteProyectil2->setPos(jugador2.x, jugador2.y);
            spriteProyectil2->setZValue(1);
            juego.cambiarTurno();
        }
    }
}

void Widget::actualizarJuego() {
    static const float dt = 0.016;

    if (proyectil1) {
        proyectil1->mover(dt);
        proyectil1->colisionarConLimites(width(), height());
        spriteProyectil->setPos(proyectil1->x, proyectil1->y);

        if (proyectil1->y >= height()) {
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;
            return;
        }

        if (spriteProyectil->collidesWithItem(vertical1) && vertical1 != nullptr) {
             vidaV1 -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaV1 <= 0)
                vertical1->setVisible(false);
                delete vertical1;
                vertical1 = nullptr;
        }
        else if (spriteProyectil->collidesWithItem(vertical2) && vertical2 != nullptr) {
            vidaV2 -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaV2 <= 0)
                vertical2->setVisible(false);
                delete vertical2;
                vertical2 = nullptr;
        }
        else if (spriteProyectil->collidesWithItem(horizontal) && horizontal != nullptr) {
            vidaH -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaH <= 0)
                horizontal->setVisible(false);
                delete horizontal;
                horizontal = nullptr;
        }

        if (spriteProyectil->collidesWithItem(muneco2) && muneco2 != nullptr) {
            vidaMuñeco2 -= 100;
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;

            if (vidaMuñeco2 <= 0) {
                muneco2->setVisible(false);
                delete muneco2;
                muneco2 = nullptr;
                mostrarMensajeVictoria("GANO EL JUGADOR 1!!!");
            }
        }

        else if (proyectil1 && (proyectil1->x < 0 || proyectil1->x > width() ||
                                proyectil1->y < 0 || proyectil1->y > height())) {
            spriteProyectil->setVisible(false);
            delete proyectil1;
            proyectil1 = nullptr;
        }
    }

    if (proyectil2) {
        proyectil2->mover(dt);
        proyectil2->colisionarConLimites(width(), height());
        spriteProyectil2->setPos(proyectil2->x, proyectil2->y);

        if (proyectil2->y >= height()) {
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;
            return;
        }

        if (spriteProyectil2->collidesWithItem(vertical3) && vertical3 != nullptr) {
            vidaV3 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaV3 <= 0)
                vertical3->setVisible(false);
                delete vertical3;
                vertical3 = nullptr;
        }

        else if (spriteProyectil2->collidesWithItem(vertical4) && vertical4 != nullptr) {
            vidaV4 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaV4 <= 0)
                vertical4->setVisible(false);
                delete vertical4;
                vertical4 = nullptr;
        }
        else if (spriteProyectil2->collidesWithItem(horizontal2) && horizontal2 != nullptr) {

            vidaH2 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaH2 <= 0)
                horizontal2->setVisible(false);
                delete horizontal2;
                horizontal2 = nullptr;
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

        if (spriteProyectil2->collidesWithItem(muneco) && muneco != nullptr) {
            vidaMuñeco1 -= 100;
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;

            if (vidaMuñeco1 <= 0) {
                muneco->setVisible(false);
                delete muneco;
                muneco = nullptr;
                mostrarMensajeVictoria("GANO EL JUGADOR 2!!!");
            }
        }

        else if (proyectil2 && (proyectil2->x < 0 || proyectil2->x > width() ||
                                proyectil2->y < 0 || proyectil2->y > height())) {
            spriteProyectil2->setVisible(false);
            delete proyectil2;
            proyectil2 = nullptr;
        }
    }

    if (juego.verificarVictoria()) {
        qDebug() << "¡El juego ha terminado!";
    }

    view->viewport()->update();
}
