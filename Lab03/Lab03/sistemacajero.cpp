#include "sistemacajero.h"
#include "codificador.h"
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
    ifstream archivo("Usuarios.txt", ios::in);
    if (!archivo.is_open()) {
        return;
    }

    string cedula, contrasenaCodificada;
    double saldo;

    while (archivo >> cedula >> contrasenaCodificada >> saldo) {
        usuarios[cedula] = {contrasenaCodificada, saldo};
    }
}

bool SistemaCajero::guardarUsuarios() {
    ofstream out("Usuarios.txt", ios::out | ios::trunc);
    if (!out.is_open()) {
        cerr << "No se pudo abrir Usuarios.txt para escribir.\n";
        return false;
    }
    for (auto& u : usuarios) {
        out << u.first << " " << u.second.first << " " << u.second.second << '\n';
    }
    out.flush();
    return static_cast<bool>(out);
}

void SistemaCajero::registrarTransaccionCodificada(const string& cedula,
                                                   const string& operacion,
                                                   double monto) {

    ostringstream claro;
    claro << "cedula:" << cedula
          << ";operacion:" << operacion
          << ";monto:" << monto;

    // Pasamos el texto a bits y aplicamos método 1
    string bits = Codificador::textoA_bits(claro.str());
    string bitsCod = Codificador::codificarBits_M1(bits, SEMILLA_N);


    ofstream log("Transacciones.txt", ios::app);
    if (!log.is_open()) {
        cerr << "No se pudo abrir Transacciones.txt para escribir.\n";
        return;
    }
    log << bitsCod << '\n';
}

void SistemaCajero::registrarUsuario(const string& cedula,
                                     const string& contrasena,
                                     double saldo) {

    string bits = Codificador::textoA_bits(contrasena);

    string bitsCod = Codificador::codificarBits_M1(bits, SEMILLA_N);

    usuarios[cedula] = {bitsCod, saldo};
    if (!guardarUsuarios()) {
        cerr << "Registrar usuario: fallo guardado; revirtiendo en memoria.\n";
        usuarios.erase(cedula);
    }
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
    if (!guardarUsuarios()) {
        cerr << "Login: fallo guardado; revirtiendo saldo en memoria.\n";
        it->second.second += 1000.0;
        return false;
    }

    registrarTransaccionCodificada(cedula, "inicio_sesion", 1000.0);
    return true;
}

bool SistemaCajero::validarAdmin(const string& contrasena) {
    ifstream f("sudo.txt");
    if (!f.is_open()) {
        cerr << "Error al abrir sudo.txt" << endl;
        return false;
    }


    string contenidoBits, linea;
    while (getline(f, linea)) {
        for (char c : linea) {
            if (c == '0' || c == '1') contenidoBits.push_back(c);
        }
    }
    f.close();

    string textoClaro;
    try {
        textoClaro = Codificador::decodificarDesdeBits(contenidoBits, SEMILLA_N);
    } catch (...) {
        cerr << "No se pudo decodificar sudo.txt (verifique la semilla n)." << endl;
        return false;
    }


    istringstream lines(textoClaro);

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

double SistemaCajero::consultarSaldo(const string& cedula) const {
    auto it = usuarios.find(cedula);
    if (it == usuarios.end()) return -1;
    return it->second.second;
}


bool SistemaCajero::retirar(const string& cedula, double monto) {
    if (monto <= 0) return false;

    auto it = usuarios.find(cedula);
    if (it == usuarios.end()) return false;

    if (it->second.second < monto) return false;

    it->second.second -= monto;
    if (!guardarUsuarios()) {
        cerr << "Retiro: fallo al guardar, revirtiendo saldo.\n";
        it->second.second += monto;
        return false;
    }

    registrarTransaccionCodificada(cedula, "retiro", monto);
    return true;
}

