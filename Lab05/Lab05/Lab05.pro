TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        caja.cpp \
        dibujo.cpp \
        main.cpp \
        obstaculo.cpp \
        particula.cpp \
        simulador.cpp \
        vector2d.cpp

HEADERS += \
    caja.h \
    dibujo.h \
    obstaculo.h \
    particula.h \
    simulador.h \
    vector2d.h
