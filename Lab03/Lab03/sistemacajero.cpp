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

void SistemaCajero::registrarUsuario(const string& cedula,
                                     const string& contrasena,
                                     double saldo) {

    string bits = Codificador::textoA_bits(contrasena);

    string bitsCod = Codificador::codificarBits_M1(bits, SEMILLA_N);

    usuarios[cedula] = {bitsCod, saldo};
    guardarUsuarios();
}


bool SistemaCajero::iniciarSesion(const string& cedula,
                                  const string& contrasena) {
    auto it = usuarios.find(cedula);
    if (it == usuarios.end()) return false;

    string bitsEntrada = Codificador::textoA_bits(contrasena);
    string bitsEntradaCod = Codificador::codificarBits_M1(bitsEntrada, SEMILLA_N);

    if (it->second.first != bitsEntradaCod) return false;

    if (it->second.second < 1000.0) return false;
    it->second.second -= 1000.0;
    guardarUsuarios();
    return true;
}

