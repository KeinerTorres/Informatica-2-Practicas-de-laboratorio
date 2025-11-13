#include "Simulador.h"
#include <iostream>
#include <cmath>
using namespace std;

Simulador::Simulador(double valorDeltaTiempo,
                     double valorTiempoFinal,
                     const Caja &caja,
                     double coeficienteRestitucion,
                     const string &nombreArchivoEstados,
                     const string &nombreArchivoColisiones)
    : deltaTiempo(valorDeltaTiempo),
    tiempoActual(0.0),
    tiempoFinal(valorTiempoFinal),
    coeficienteRestitucionObstaculos(coeficienteRestitucion),
    cajaSimulacion(caja)
{
    archivoEstados.open(nombreArchivoEstados);
    if (!archivoEstados.is_open())
    {
        cerr << "Error al abrir el archivo de estados.\n";
    }
    else
    {
        archivoEstados << "tiempo,id,x,y,vx,vy\n";
    }

    archivoColisiones.open(nombreArchivoColisiones);
    if (!archivoColisiones.is_open())
    {
        cerr << "Error al abrir el archivo de colisiones.\n";
    }
    else
    {
        archivoColisiones << "tiempo,tipo,id1,id2,descripcion\n";
    }
}

Simulador::~Simulador()
{
    if (archivoEstados.is_open())
        archivoEstados.close();
    if (archivoColisiones.is_open())
        archivoColisiones.close();
}

void Simulador::agregarParticula(const Particula &particula)
{
    listaDeParticulas.push_back(particula);
}

void Simulador::agregarObstaculo(const Obstaculo &obstaculo)
{
    listaDeObstaculos.push_back(obstaculo);
}

void Simulador::ejecutarPaso()
{
    for (Particula &particula : listaDeParticulas)
    {
        particula.actualizar(deltaTiempo);
    }

    manejarColisionesConCaja();
    manejarColisionesConObstaculos();
    manejarColisionesEntreParticulas();
    registrarEstadoActual();
    tiempoActual += deltaTiempo;
}

void Simulador::ejecutarSimulacion()
{
    while (tiempoActual <= tiempoFinal)
    {
        ejecutarPaso();
    }
}

void Simulador::registrarEstadoActual()
{
    if (!archivoEstados.is_open())
        return;

    for (const Particula &p : listaDeParticulas)
    {
        if (!p.estaActiva())
            continue;

        const Vector2D &pos = p.obtenerPosicion();
        const Vector2D &vel = p.obtenerVelocidad();

        archivoEstados << tiempoActual << ","
                       << p.obtenerIdentificador() << ","
                       << pos.componenteX << ","
                       << pos.componenteY << ","
                       << vel.componenteX << ","
                       << vel.componenteY << "\n";
    }
}

void Simulador::registrarColision(const string &tipo,
                                  int id1,
                                  int id2,
                                  const string &descripcion)
{
    if (!archivoColisiones.is_open())
        return;

    archivoColisiones << tiempoActual << ","
                      << tipo << ","
                      << id1 << ","
                      << id2 << ","
                      << descripcion << "\n";
}

void Simulador::manejarColisionesConCaja()
{
    for (Particula &particula : listaDeParticulas)
    {
        if (!particula.estaActiva())
            continue;

        Vector2D velocidadAntes = particula.obtenerVelocidad();
        cajaSimulacion.manejarColisionConParticula(particula);
        Vector2D velocidadDespues = particula.obtenerVelocidad();

        if (velocidadAntes.componenteX != velocidadDespues.componenteX ||
            velocidadAntes.componenteY != velocidadDespues.componenteY)
        {
            registrarColision("PARED",
                              particula.obtenerIdentificador(),
                              -1,
                              "");
        }
    }
}

void Simulador::manejarColisionesConObstaculos()
{
    for (Particula &particula : listaDeParticulas)
    {
        if (!particula.estaActiva())
            continue;

        for (size_t indice = 0; indice < listaDeObstaculos.size(); ++indice)
        {
            Vector2D normalColision;
            if (listaDeObstaculos[indice].verificarColisionConParticula(particula, normalColision))
            {
                Vector2D velocidad = particula.obtenerVelocidad();

                double componenteNormal = velocidad.productoPunto(normalColision);
                Vector2D velocidadPerpendicular = normalColision.multiplicarPorEscalar(componenteNormal);
                Vector2D velocidadParalela = velocidad.restar(velocidadPerpendicular);

                Vector2D velocidadPerpendicularNueva =
                    velocidadPerpendicular.multiplicarPorEscalar(-coeficienteRestitucionObstaculos);

                Vector2D velocidadNueva = velocidadParalela.sumar(velocidadPerpendicularNueva);
                particula.establecerVelocidad(velocidadNueva);

                registrarColision("PARTICULA_OBSTACULO",
                                  particula.obtenerIdentificador(),
                                  static_cast<int>(indice),
                                  "");
            }
        }
    }
}

void Simulador::fusionarParticulas(Particula &a, Particula &b)
{
    double masaTotal = a.obtenerMasa() + b.obtenerMasa();
    Vector2D velocidadNueva(
        (a.obtenerVelocidad().componenteX * a.obtenerMasa() + b.obtenerVelocidad().componenteX * b.obtenerMasa()) / masaTotal,
        (a.obtenerVelocidad().componenteY * a.obtenerMasa() + b.obtenerVelocidad().componenteY * b.obtenerMasa()) / masaTotal);

    Vector2D posicionNueva(
        (a.obtenerPosicion().componenteX * a.obtenerMasa() + b.obtenerPosicion().componenteX * b.obtenerMasa()) / masaTotal,
        (a.obtenerPosicion().componenteY * a.obtenerMasa() + b.obtenerPosicion().componenteY * b.obtenerMasa()) / masaTotal);

    double nuevoRadio = sqrt(pow(a.obtenerRadio(), 2) + pow(b.obtenerRadio(), 2));

    a.establecerMasa(masaTotal);
    a.establecerVelocidad(velocidadNueva);
    a.establecerPosicion(posicionNueva);
    a.establecerRadio(nuevoRadio);

    b.establecerActiva(false);
}

void Simulador::manejarColisionesEntreParticulas()
{
    for (size_t i = 0; i < listaDeParticulas.size(); ++i)
    {
        if (!listaDeParticulas[i].estaActiva())
            continue;

        for (size_t j = i + 1; j < listaDeParticulas.size(); ++j)
        {
            if (!listaDeParticulas[j].estaActiva())
                continue;

            Vector2D diferencia = listaDeParticulas[j].obtenerPosicion().restar(listaDeParticulas[i].obtenerPosicion());
            double distancia = diferencia.obtenerLongitud();
            double sumaRadios = listaDeParticulas[i].obtenerRadio() + listaDeParticulas[j].obtenerRadio();

            if (distancia <= sumaRadios)
            {
                registrarColision("PARTICULA_PARTICULA",
                                  listaDeParticulas[i].obtenerIdentificador(),
                                  listaDeParticulas[j].obtenerIdentificador(),
                                  "fusion");
                fusionarParticulas(listaDeParticulas[i], listaDeParticulas[j]);
            }
        }
    }
}
