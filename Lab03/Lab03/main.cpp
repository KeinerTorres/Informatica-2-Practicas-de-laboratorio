#include "sistemacajero.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

static void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    cout << fixed << setprecision(0);

    SistemaCajero cajero;
    string usuarioActivo = "";

    int opcion;
    do {
        cout << "\n       CAJERO      \n";
        cout << "1) Registrar usuario\n";
        cout << "2) Iniciar sesion (cobra 1000 COP)\n";
        cout << "3) Consultar saldo\n";
        cout << "4) Retirar dinero\n";
        cout << "5) Validar administrador (sudo.txt)\n";
        cout << "6) Salir\n";
        cout << "7) Cerrar sesion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            limpiarEntrada();
            cout << "Entrada invalida.\n";
            continue;
        }

        limpiarEntrada();

        if (opcion == 1) {
            string cedula, clave;
            double saldo;

            cout << "Ingrese la cedula: ";
            cin >> cedula;
            limpiarEntrada();

            cout << "Ingrese la contrasena (se guardara codificada): ";
            cin >> clave;
            limpiarEntrada();

            cout << "Ingrese el saldo inicial: ";
            if (!(cin >> saldo)) {
                limpiarEntrada();
                cout << "Saldo invalido.\n";
                pausar();
                continue;
            }
            limpiarEntrada();

            cajero.registrarUsuario(cedula, clave, saldo);
            cout << "Usuario registrado.\n";
            pausar();

        } else if (opcion == 2) {
            string cedula, clave;

            cout << "Cedula: ";
            cin >> cedula;
            limpiarEntrada();

            cout << "Contrasena: ";
            cin >> clave;
            limpiarEntrada();

            if (cajero.iniciarSesion(cedula, clave)) {
                usuarioActivo = cedula;
                cout << "Inicio de sesion exitoso. Se descontaron 1000 COP.\n";
            } else {
                double s = cajero.consultarSaldo(cedula);
                if (s >= 0 && s < 1000) {
                    cout << "Inicio de sesion FALLIDO: saldo insuficiente para el cobro de 1000.\n";
                } else {
                    cout << "Inicio de sesion FALLIDO: cedula o contrasena incorrecta.\n";
                }
            }
            pausar();

        } else if (opcion == 3) {
            if (usuarioActivo.empty()) {
                cout << "Debe iniciar sesion primero.\n";
            } else {
                double saldo = cajero.consultarSaldo(usuarioActivo);
                if (saldo < 0) {
                    cout << "No se pudo consultar el saldo.\n";
                } else {
                    cout << "Saldo actual: " << saldo << " COP\n";
                }
            }
            pausar();

        } else if (opcion == 4) {
            if (usuarioActivo.empty()) {
                cout << "Debe iniciar sesion primero.\n";
                pausar();
            } else {
                double monto;
                cout << "Monto a retirar: ";
                if (!(cin >> monto)) {
                    limpiarEntrada();
                    cout << "Monto invalido.\n";
                    pausar();
                    continue;
                }
                limpiarEntrada();

                if (cajero.retirar(usuarioActivo, monto)) {
                    cout << "Retiro exitoso.\n";
                    cout << "Nuevo saldo: " << cajero.consultarSaldo(usuarioActivo) << " COP\n";
                } else {
                    cout << "No se pudo realizar el retiro (fondos insuficientes o error).\n";
                }
                pausar();
            }

        } else if (opcion == 5) {
            string clave;
            cout << "Ingrese la clave de administrador: ";
            cin >> clave;
            limpiarEntrada();

            if (cajero.validarAdmin(clave)) {
                cout << "Administrador validado correctamente.\n";
            } else {
                cout << "Clave de administrador incorrecta.\n";
            }
            pausar();

        } else if (opcion == 7) {
            if (usuarioActivo.empty()) {
                cout << "No hay ninguna sesion activa.\n";
            } else {
                usuarioActivo.clear();
                cout << "Sesion cerrada correctamente.\n";
            }
            pausar();

        } else if (opcion == 6) {
            cout << "Saliendo...\n";
            // no pausar al salir
        } else {
            cout << "Opcion no valida.\n";
            pausar();
        }

    } while (opcion != 6);

    return 0;
}
