#include "Red.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
    Red red;
    cout << "Bienvenido al simulador de red de enrutadores" << endl;

    while (true) {
        cout << "\n--- Menu de opciones ---" << endl;
        cout << "1. Agregar un router" << endl;
        cout << "2. Eliminar un router" << endl;
        cout << "3. Conectar routers / actualizar costo" << endl;
        cout << "4. Desconectar routers" << endl;
        cout << "5. Mostrar estado actual de la red" << endl;
        cout << "6. Mostrar tablas de enrutamiento" << endl;
        cout << "7. Mostrar camino mas corto entre dos routers" << endl;
        cout << "8. Cargar red desde archivo" << endl;
        cout << "9. Guardar red en archivo" << endl;
        cout << "10. Generar red aleatoria" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";

        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente nuevamente." << endl;
            continue;
        }
        if (opcion == 0) {
            cout << "Gracias por utilizar el simulador. Hasta luego." << endl;
            break;
        }

        switch (opcion) {
        case 1: {
            string nombre;
            cout << "Nombre del nuevo router: ";
            cin >> nombre;
            red.agregarRouter(nombre);
            break;
        }
        case 2: {
            string nombre;
            cout << "Nombre del router a eliminar: ";
            cin >> nombre;
            red.eliminarRouter(nombre);
            break;
        }
        case 3: {
            string r1, r2;
            int costo;
            cout << "Nombre del primer router: ";
            cin >> r1;
            cout << "Nombre del segundo router: ";
            cin >> r2;
            cout << "Costo del enlace: ";
            cin >> costo;
            red.conectarRouters(r1, r2, costo);
            break;
        }
        case 4: {
            string r1, r2;
            cout << "Nombre del primer router: ";
            cin >> r1;
            cout << "Nombre del segundo router: ";
            cin >> r2;
            red.desconectarRouters(r1, r2);
            break;
        }
        case 5:
            red.mostrarEstadoRed();
            break;
        case 6:
            red.mostrarTablasEnrutamiento();
            break;
        case 7: {
            string origen, destino;
            cout << "Router origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.mostrarRutaMinima(origen, destino);
            break;
        }
        case 8: {
            string ruta;
            cout << "Ruta del archivo a cargar: ";
            cin >> ruta;
            red.cargarDesdeArchivo(ruta);
            break;
        }
        case 9: {
            string ruta;
            cout << "Ruta del archivo para guardar: ";
            cin >> ruta;
            red.guardarEnArchivo(ruta);
            break;
        }
        case 10: {
            int n, costoMin, costoMax;
            double densidad;
            cout << "Numero de routers: ";
            cin >> n;
            cout << "Densidad de enlaces (0.0 - 1.0): ";
            cin >> densidad;
            cout << "Costo minimo: ";
            cin >> costoMin;
            cout << "Costo maximo: ";
            cin >> costoMax;
            red.generarRedAleatoria(n, densidad, costoMin, costoMax);
            break;
        }
        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
            break;
        }
    }
    return 0;
}

