#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <string>
using namespace std;

class Codificador {
public:
    // Este es para modificar el texto usando el metodo 1
    static string codificar(const string& textoClaro, int n);

    // Decodifica el texto invirtiendo el proceso
    static string decodificar(const string& textoCodificado, int n);

    static string codificarSoloBits(const string& textoClaro, int n);
    static string decodificarDesdeBits(const string& bitsCodificados, int n);

    // Hace la conversion texto a bits
    static string textoA_bits(const string& s);
    static string bitsA_texto(const string& bits);

    // Núcleo del método 1 sobre cadenas de bits
    static string codificarBits_M1(const string& bits, int n);
    static string decodificarBits_M1(const string& bitsCod, int n);
private:
    // Reglas de inversión por bloque
    static string invertirTodos(const string& b);
    static string invertirCadaK(const string& b, int k);
};

#endif // CODIFICADOR_H
