#include "vectorSufijos.hpp"
#include <algorithm>
#include <string.h>
#include <stdlib.h>


void VectorSufijos::ordenar(){
    // Ordenar esos indices segun los sufijos en orden alfabetico
    std::sort(indices, indices + tam, [this](int a, int b) {return strcmp(cad+a, cad+b) < 0;});
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
    this->cad[l-1] = '$';
    this->cad[l] = '\0';

    // Crear vector de indices
    this->indices = (int*)malloc((l+1)*sizeof(int));
    for(int i = 0; i <= l; i++){
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