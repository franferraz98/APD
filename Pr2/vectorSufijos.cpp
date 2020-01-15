#include "vectorSufijos.hpp"
#include <string.h>
#include <stdlib.h>

VectorSufijos::VectorSufijos(const char * c){
    int l = strlen(c);
    this->cad = (char*)malloc(l*sizeof(char));
    strcpy(this->cad,c);
    this->tam = l;
}

VectorSufijos::~VectorSufijos(){
    delete(this->cad);
}

int VectorSufijos::len() const {
    return this->tam;
}

const char * VectorSufijos::operator[](const int idx) const{
    return this->cad+idx;
}