#include "burrowsWheeler.hpp"
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>



typedef std::tuple<char, char> tuplaChars;
typedef std::tuple<char, int> tuplaCharIndex;

char BurrowsWheeler::caracter(const VectorSufijos &v, const int i, const int j){
    return v.sufijo(0)[(i+v.indice(j)) % (v.len())];
}

std::string BurrowsWheeler::columna(const VectorSufijos &v, const int c){
    // Devolver ultima columna de la matriz de Burrows
    std::string res = "";
    for(int i = 0; i < v.len(); i++){
        res += BurrowsWheeler::caracter(v, c, i);
    }
    return res;
}

bool compCharIndex(tuplaCharIndex a, tuplaCharIndex b){ return std::get<0>(a) < std::get<0>(b) || (std::get<0>(a) == std::get<0>(b) && std::get<1>(a) < std::get<1>(b));}

std::string BurrowsWheeler::compress(const char * c){
    // Crear vector de sufijos
    VectorSufijos v(c);

    // Ordenar sufijos alfabeticamente
    v.ordenar();

    // Devolver ultima columna de la matriz de Burrows correspondiente
    std::string res = columna(v, v.len()-1);

    return res;
}

std::string BurrowsWheeler::decompress(const char * c){
    int l = strlen(c);

    // Crear columna izda (guardando indices en col dcha)
    std::vector<tuplaCharIndex> colIzda;
    colIzda.resize(l);
    for(int i = 0; i < l; i++) {
        colIzda[i] = tuplaCharIndex(c[i], i);
    }
    // Ordenar en orden alfabetico
    std::sort(colIzda.begin(), colIzda.end(), compCharIndex);
    
    // Buscar principio de la cadena (caracter dolar)
    std::string res(c);
    int idxDcha = 0;
    bool found = false;
    for(int i = 0; i < l; i++){
        if(std::get<0>(colIzda[i]) == EOF_CHAR){
            idxDcha = i;
            found = true;
            break;
        }
    }
    if (!found){
        std::cout << "WTF" << std::endl;
    }

    // Reconstruir la cadena original iterando la columna de la izda
    idxDcha = std::get<1>(colIzda[idxDcha]);
    for(int i = 0; i < l; i++){
        res[i] = std::get<0>(colIzda[idxDcha]);
        idxDcha = std::get<1>(colIzda[idxDcha]);
    }
    
    // Eliminar el caracter $ del final
    res[l-1] = '\0';

    return res;
}