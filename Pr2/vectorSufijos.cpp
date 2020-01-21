#include "vectorSufijos.hpp"
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

bool comparaSufijos(struct Sufijo a, struct Sufijo b){ return (a.rango[0] == b.rango[0])? (a.rango[1] < b.rango[1] ?1: 0): 
               (a.rango[0] < b.rango[0] ?1: 0); }


void VectorSufijos::radix(const int col, const int j_0, const int j_f){
    // Count digit (char) appearances
    int array[256] = {0};
    for(int i = j_0; i<= j_f; i++){
        array[(*this)[i][col]]++;
    }

    //Create count array
    for(int i = 1; i < 256; i++){
        array[i] += array[i-1];
    }

    //Copy count array
    int count_array[256];
    memcpy(count_array, array, sizeof(array));

    // Order using count array
    int *res = (int*)malloc((j_f-j_0+1)*sizeof(int));
    for(int i = j_f; i>= j_0; i--){
        int res_idx = --array[(*this)[i][col]];
        res[res_idx] = this->indice(i);
    }
    // Set new order to indices
    for(int i = 0; i < j_f - j_0 + 1; i++){
        this->indices[j_0+i] = res[i];
    }
    delete(res);

    //Continue ordering next column
    int r_0 = 0;
    for(int i = 0; i < 256; i++){
        int r_f = array[i]-1;
        if(r_f > r_0){
            VectorSufijos::radix(col-1, j_0+r_0, j_0+r_f);
        }
        r_0 = r_f+1;
    }

}
void VectorSufijos::ordenar(){
    int *indices2 = (int*)malloc(tam * sizeof(int));
    memcpy(indices2, indices, tam * sizeof(int));

    // Ordenar esos indices segun los sufijos en orden alfabetico
    std::sort(indices, indices + tam, [this](int a, int b) {return strcmp(cad+a, cad+b) < 0;});


    /*
    std::cout << std::endl;
    for(int i = 0; i < tam; i++){
        std::cout << indices[i] << ", ";
    }
    std::cout << std::endl;

    std::swap(indices, indices2);

    VectorSufijos::radix(tam-1, 0, tam-1);
    for(int i = 0; i < tam; i++){
        std::cout << indices[i] << ", ";
    }
    std::cout << std::endl;

    if(memcmp(indices2, indices, tam * sizeof(int)) != 0){
        throw;
    }
    */
}

int VectorSufijos::indice(int idx) const{
    return this->indices[idx];
}

VectorSufijos::VectorSufijos(const char * c){
    // Guardar tamaño del vector de sufijos
    int l = strlen(c) + 1;
    this->tam = l;

    // Guardar cadena original con $ al final
    this->cad = (char*)malloc(l*sizeof(char));
    strcpy(this->cad,c);
    this->cad[l-1] = EOF_CHAR;
    this->cad[l] = '\0';
   

    // Crear vector de indices
    this->indices = (int*)malloc(l*sizeof(int));
    for(int i = 0; i < l; i++){
        indices[i] = i;
    }
}

VectorSufijos::~VectorSufijos(){
    delete(this->cad);
}

int VectorSufijos::len() const {
    return this->tam;
}

const char * VectorSufijos::operator[](const int idx) const{
    return this->sufijo(this->indice(idx));
}
const char * VectorSufijos::sufijo(const int id) const{
    return this->cad+id;
}

void VectorSufijos::print() {
    for(int i=0; i<this->tam; i++){
        std::cout << indices[i];
    }
    std::cout << std::endl;
}