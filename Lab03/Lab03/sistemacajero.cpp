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
    out.close();
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
    const bool DEBUG = true;

    ifstream f("sudo.txt");
    if (!f.is_open()) {
        f.open("sudo");
        if (!f.is_open()) {
            cerr << "Error al abrir sudo.txt" << endl;
            return false;
        }
    }


    string contenidoBits, linea;
    while (getline(f, linea)) {
        for (char c : linea) {
            if (c == '0' || c == '1') contenidoBits.push_back(c);
        }
    }
    f.close();

    if (contenidoBits.empty() || (contenidoBits.size() % 8) != 0) {
        cerr << "sudo.txt no contiene un número válido de bits (múltiplo de 8 requerido).\n";
        return false;
    }
    string textoClaro;

    try {
        textoClaro = Codificador::decodificarDesdeBits(contenidoBits, SEMILLA_N);
    } catch (...) {
        cerr << "No se pudo decodificar sudo.txt (verifique la semilla n)." << endl;
        return false;
    }

    auto trim = [](string& s) {
        auto ws = [](unsigned char ch){ return ch==' '||ch=='\t'||ch=='\r'||ch=='\n'; };
        size_t i=0, j=s.size();
        while (i<j && ws((unsigned char)s[i])) ++i;
        while (j>i && ws((unsigned char)s[j-1])) --j;
        if (i>0 || j<s.size()) s = s.substr(i, j-i);
    };

    istringstream in(textoClaro);
    while (getline(in, linea)) {
        string l = linea;
        trim(l);
        if (l.rfind("clave:", 0) == 0) {
            string cla = l.substr(6);
            trim(cla);
            if (cla == contrasena) {
                return true;
            }
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

