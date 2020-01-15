#include "burrowsWheeler.hpp"
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>

typedef std::tuple<char, char> tuplaChars;

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

std::string BurrowsWheeler::compress(const char * c){
    VectorSufijos v(c);

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

std::string BurrowsWheeler::decompress(const char * c, char begin){
    // Ordernar texto para sacar columna izda
    std::string ultCol(c);
    std::sort(ultCol.begin(), ultCol.end());

    int l = strlen(c);
    std::string res(c);

    char buscar = begin;
    int subindice = 1;
    for(int i = 0; i < l; i++){
        for(int j = 0; j < l; j++) {
            if(ultCol[j] == buscar){
                res[i] = buscar;
                buscar = c[j];
                ultCol[j] = '\0';
                break;
            }
        }
    }
    


    return res;
}