#ifndef BURROWS_HH
#define BURROWS_HH

#include "vectorSufijos.cpp"
#include <string>

class BurrowsWheeler {
protected:
    static char caracter(const VectorSufijos &v, const int i, const int j);
    static std::string columna(const VectorSufijos &v, const int i);
public:
    static std::string compress(const char * c);
    static std::string decompress(const char * c, char begin);
};

#endif