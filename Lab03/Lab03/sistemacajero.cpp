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

bool SistemaCajero::validarAdmin(const string& contrasena) {
    ifstream f("sudo.txt", ios::binary);
    if (!f.is_open()) {
        cerr << "Error al abrir sudo.txt" << endl;
        return false;
    }


    string contenidoCod((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    f.close();

    string textoClaro;
    try {
        textoClaro = Codificador::decodificar(contenidoCod, SEMILLA_N);
    } catch (...) {
        cerr << "No se pudo decodificar sudo.txt (verifique la semilla n)." << endl;
        return false;
    }


    istringstream lines(textoClaro);
    string linea;

    while (true) {
        string ced, usu, cla, sal;

        // Para cédula
        if (!getline(lines, linea)) break;
        if (linea.rfind("cedula:", 0) != 0) continue;
        ced = linea.substr(7);
        if (!ced.empty() && ced[0] == ' ') ced.erase(0, 1);

        // Para usuario
        if (!getline(lines, linea)) break;
        if (linea.rfind("usuario:", 0) != 0) continue;
        usu = linea.substr(8);
        if (!usu.empty() && usu[0] == ' ') usu.erase(0, 1);

        // Para clave
        if (!getline(lines, linea)) break;
        if (linea.rfind("clave:", 0) != 0) continue;
        cla = linea.substr(6);
        if (!cla.empty() && cla[0] == ' ') cla.erase(0, 1);

        // Para saldo
        if (!getline(lines, linea)) break;
        if (linea.rfind("saldo:", 0) != 0) continue;
        sal = linea.substr(6);
        if (!sal.empty() && sal[0] == ' ') sal.erase(0, 1);


        getline(lines, linea);


        if (cla == contrasena) {
            return true;
        }
    }

    return false;
}
