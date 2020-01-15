#include "burrowsWheeler.hpp"
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>

typedef std::tuple<char, char> tuplaChars;
typedef std::tuple<char, int> tuplaCharIndex;

char BurrowsWheeler::caracter(const VectorSufijos &v, const int i, const int j){
    return v[(i+j)%v.len()][0];
}

std::string BurrowsWheeler::columna(const VectorSufijos &v, const int i){
    std::string res = "";
    for(int j = 0; j < v.len(); j++){
        res += caracter(v, i, j);
    }
    return res;
}

bool firstCharLessThan(tuplaChars a, tuplaChars b){ return std::get<0>(a) < std::get<0>(b);}
bool compCharIndex(tuplaCharIndex a, tuplaCharIndex b){ return std::get<0>(a) < std::get<0>(b);}

std::string BurrowsWheeler::compress(const char * c){
    VectorSufijos v(c);

    // Crear un array con los indices de los sufijos en la matriz de burrows wheeler
    std::vector<int> indices;
    indices.resize(v.len()+1);

    //int indices[v.len()];
    for(int i = 0; i <= v.len(); i++) {
        indices[i] = i;
    }

    // Ordenar esos indices segun los sufijos en orden alfabetico
    std::sort(indices.begin(), indices.end(), [c](int a, int b) {return strcmp(c+a, c+b) < 0;});

    // Devolver ultima columna 
    std::string res = "";
    for(int i = 0; i <= v.len(); i++){
        res += v[0][(v.len()+indices[i]) % (v.len()+1)];
    } 

    return res;

    std::string primCol = columna(v, 0);
    std::string ultCol = columna(v, v.len()-1);



    // char array[v.len()][2];

    std::vector<tuplaChars> array;
    array.resize(v.len());

    for(int i = 0; i < v.len(); i++) {
        array[i] = tuplaChars (ultCol[(i+1)%v.len()], primCol[(i+1)%v.len()]);
    }

    std::sort(array.begin(), array.end(), firstCharLessThan);
    
    for (int j = 0; j < v.len(); j++) {
        primCol[j] = std::get<0>(array[j]);
        ultCol[j] = std::get<1>(array[j]);
    }
    std::cout << "Prim: " << primCol << std::endl;

    return ultCol;
}

std::string BurrowsWheeler::decompress(const char * c){
    
    int l = strlen(c);

    // Ordernar texto para sacar columna izda (guardando indices de col dcha)
    std::vector<tuplaCharIndex> colIzda;
    colIzda.resize(l);

    for(int i = 0; i < l; i++) {
        colIzda[i] = tuplaCharIndex(c[i], i);
    }
    std::sort(colIzda.begin(), colIzda.end(), compCharIndex);
    
    // Reconstruir la cadena original iterando la columna de la izda
    std::string res(c);
    int buscar = 0;
    buscar = std::get<1>(colIzda[buscar]);
    for(int i = 0; i < l; i++){
        res[i] = std::get<0>(colIzda[buscar]);
        buscar = std::get<1>(colIzda[buscar]);
    }
    
    // Eliminar el caracter $ del final
    res[l-1] = '\0';

    return res;
}