#include "codificador.h"
#include <stdexcept>
using namespace std;


string Codificador::textoA_bits(const string& s) {
    string out; out.reserve(s.size() * 8);
    for (unsigned char c : s) {
        for (int i = 7; i >= 0; --i) {
            out.push_back( ( (c >> i) & 1 ) ? '1' : '0' );
        }
    }
    return out;
}

string Codificador::bitsA_texto(const string& bits) {
    string out;
    size_t n = bits.size() / 8;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned char val = 0;
        for (int j = 0; j < 8; ++j) {
            val <<= 1;
            char b = bits[i*8 + j];
            if (b == '1') val |= 1;
        }
        out.push_back(static_cast<char>(val));
    }
    return out;
}

string Codificador::invertirTodos(const string& b) {
    string out = b;
    for (char& ch : out) ch = (ch == '0') ? '1' : '0';
    return out;
}


string Codificador::invertirCadaK(const string& b, int k) {
    string out = b;
    for (size_t i = 0; i < out.size(); ++i) {
        size_t pos1 = i + 1; // 1-index
        if (k > 0 && (pos1 % k == 0)) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }
    return out;
}


string Codificador::codificarBits_M1(const string& bits, int n) {
    if (n <= 0) throw invalid_argument("n debe ser > 0");
    string resultado; resultado.reserve(bits.size());


    for (size_t i = 0; i < bits.size(); i += n) {
        string bloque = bits.substr(i, n);

        if (i == 0) {
            // Primer bloque: invertir todos los bits
            string enc = invertirTodos(bloque);
            resultado += enc;
        } else {

            string bloquePrevOriginal = bits.substr(i - n, n);

            int ceros = 0, unos = 0;
            for (char b : bloquePrevOriginal) (b == '0') ? ++ceros : ++unos;

            string enc;
            if (ceros == unos) {
                enc = invertirTodos(bloque);
            } else if (ceros > unos) {
                enc = invertirCadaK(bloque, 2);
            } else {
                enc = invertirCadaK(bloque, 3);
            }
            resultado += enc;
        }
    }
    return resultado;
}


string Codificador::decodificarBits_M1(const string& bitsCod, int n) {
    if (n <= 0) throw invalid_argument("n debe ser > 0");
    string resultado; resultado.reserve(bitsCod.size());

    for (size_t i = 0; i < bitsCod.size(); i += n) {
        string bloqueCod = bitsCod.substr(i, n);

        if (i == 0) {
            // Primer bloque: volver a invertir para recuperar el original
            string orig = invertirTodos(bloqueCod);
            resultado += orig;
        } else {
            string bloquePrevOriginal = resultado.substr(i - n, n);
            int ceros = 0, unos = 0;
            for (char b : bloquePrevOriginal) (b == '0') ? ++ceros : ++unos;

            string orig;
            if (ceros == unos) {
                orig = invertirTodos(bloqueCod);
            } else if (ceros > unos) {

                orig = invertirCadaK(bloqueCod, 2);
            } else {

                orig = invertirCadaK(bloqueCod, 3);
            }
            resultado += orig;
        }
    }
    return resultado;
}


string Codificador::codificar(const string& textoClaro, int n) {
    string bits = textoA_bits(textoClaro);
    string bitsCod = codificarBits_M1(bits, n);
    return bitsA_texto(bitsCod);
}

string Codificador::decodificar(const string& textoCodificado, int n) {
    string bitsCod = textoA_bits(textoCodificado);
    string bitsOrig = decodificarBits_M1(bitsCod, n);
    return bitsA_texto(bitsOrig);
}

string Codificador::codificarSoloBits(const string& textoClaro, int n) {
    string bits = textoA_bits(textoClaro);
    return codificarBits_M1(bits, n);
}

string Codificador::decodificarDesdeBits(const string& bitsCodificados, int n) {
    string bitsOrig = decodificarBits_M1(bitsCodificados, n);
    return bitsA_texto(bitsOrig);
}
