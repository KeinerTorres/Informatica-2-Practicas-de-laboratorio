#include <iostream>
#include "Simulador.h"
#include "Caja.h"
#include "Particula.h"
#include "Obstaculo.h"
#include "Vector2D.h"

using namespace std;

int main()
{
    double deltaTiempo = 0.01;
    double tiempoFinal = 10.0;

    double limiteIzquierdo = 0.0;
    double limiteDerecho  = 100.0;
    double limiteInferior = 0.0;
    double limiteSuperior = 100.0;

    double coeficienteRestitucionObstaculos = 0.5;

    Caja cajaSimulacion(limiteIzquierdo,
                        limiteDerecho,
                        limiteInferior,
                        limiteSuperior);

    Simulador simulador(deltaTiempo,
                        tiempoFinal,
                        cajaSimulacion,
                        coeficienteRestitucionObstaculos,
                        "estados.txt",
                        "colisiones.txt");

    Particula particulaUno(0,
                           Vector2D(20.0, 20.0),
                           Vector2D(15.0, 10.0),
                           1.0,
                           2.0);

    Particula particulaDos(1,
                           Vector2D(80.0, 50.0),
                           Vector2D(-20.0, -5.0),
                           1.5,
                           3.0);

    Particula particulaTres(2,
                            Vector2D(50.0, 80.0),
                            Vector2D(0.0, -30.0),
                            2.0,
                            2.5);

    Particula particulaCuatro(3,
                              Vector2D(10.0, 60.0),
                              Vector2D(25.0, -15.0),
                              0.8,
                              2.0);

    simulador.agregarParticula(particulaUno);
    simulador.agregarParticula(particulaDos);
    simulador.agregarParticula(particulaTres);
    simulador.agregarParticula(particulaCuatro);

    Obstaculo obstaculoUno   (Vector2D(30.0, 30.0), 10.0, 10.0);
    Obstaculo obstaculoDos   (Vector2D(70.0, 30.0), 10.0, 10.0);
    Obstaculo obstaculoTres  (Vector2D(30.0, 70.0), 10.0, 10.0);
    Obstaculo obstaculoCuatro(Vector2D(70.0, 70.0), 10.0, 10.0);

    simulador.agregarObstaculo(obstaculoUno);
    simulador.agregarObstaculo(obstaculoDos);
    simulador.agregarObstaculo(obstaculoTres);
    simulador.agregarObstaculo(obstaculoCuatro);

    simulador.ejecutarSimulacion();

    cout << "Simulacion finalizada. Revisa 'estados.txt', 'colisiones.txt'.\n";
    return 0;
}
