#ifndef SISTEMACAJERO_H
#define SISTEMACAJERO_H

#include <string>
#include <map> // Lo usare para almacenar los usuarios y sus datos
using namespace std;

class SistemaCajero {
private:
    map<string, pair<string, double>> usuarios;

    // Para cargar los usuarios desde el archivo (Usuarios.txt)
    void cargarUsuarios();

    // Para guardar los usuarios en el archivo (Usuarios.txt)
    void guardarUsuarios();

public:
    SistemaCajero();
    ~SistemaCajero();
};

#endif // SISTEMACAJERO_H
