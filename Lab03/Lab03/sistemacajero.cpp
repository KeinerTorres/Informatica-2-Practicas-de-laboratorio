#include "SistemaCajero.h"
#include "Codificador.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


static const int SEMILLA_N = 4;



SistemaCajero::SistemaCajero() {

    cargarUsuarios();
}

SistemaCajero::~SistemaCajero() {
    guardarUsuarios();
}

void SistemaCajero::cargarUsuarios() {
    ifstream archivo("Usuarios.txt");
    if (!archivo.is_open()) {
        return;
    }

    string cedula, contrasenaCodificada;
    double saldo;

    while (archivo >> cedula >> contrasenaCodificada >> saldo) {
        usuarios[cedula] = {contrasenaCodificada, saldo};
    }
}

void SistemaCajero::guardarUsuarios() {
    ofstream archivo("Usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir Usuarios.txt para escribir." << endl;
        return;
    }

    for (auto& u : usuarios) {

        archivo << u.first << " "            // Para cédula
                << u.second.first << " "     // Para contraseña codificada
                << u.second.second << "\n";  // Para saldo
    }
}
