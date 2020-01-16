#include "vectorSufijos.hpp"
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

bool comparaSufijos(struct Sufijo a, struct Sufijo b){ return (a.rango[0] == b.rango[0])? (a.rango[1] < b.rango[1] ?1: 0): 
               (a.rango[0] < b.rango[0] ?1: 0); }

VectorSufijos::VectorSufijos(const char * c){

    int m = strlen(c);
    this->cad = (char*)malloc(m*sizeof(char)+1);
    strcpy(this->cad,c);
    this->cad[m] = '$';
    this->cad[m+1] = '\0';
    this->tam = m;

    int l = strlen(c);

    this->numElem = l;

    struct Sufijo sufijos[l];

    for (int i = 0; i < l; i++) 
    { 
        sufijos[i].indice = i; 
        sufijos[i].rango[0] = c[i]; 
        sufijos[i].rango[1] = ((i+1) < l)? (c[i + 1]): -1; 
    } 

    std::sort(sufijos, sufijos+l, comparaSufijos);

    int idx[l];

    for (int k = 4; k < 2*l; k = k*2) 
    { 
        // Assigning rank and index values to first suffix 
        int rang = 0; 
        int ant_rang = sufijos[0].rango[0]; 
        sufijos[0].rango[0] = rang; 
        idx[sufijos[0].indice] = 0; 
  
        // Assigning rango to sufijos 
        for (int i = 1; i < l; i++) 
        { 
            // If first rango and next rangos are same as that of previous 
            // suffix in array, assign the same new rango to this suffix 
            if (sufijos[i].rango[0] == ant_rang && 
                    sufijos[i].rango[1] == sufijos[i-1].rango[1]) 
            { 
                ant_rang = sufijos[i].rango[0]; 
                sufijos[i].rango[0] = rang; 
            } 
            else // Otherwise increment rango and assign 
            { 
                ant_rang = sufijos[i].rango[0]; 
                sufijos[i].rango[0] = ++rang; 
            } 
            idx[sufijos[i].indice] = i; 
        } 
  
        // Assign next rango to every suffix 
        for (int i = 0; i < l; i++) 
        { 
            int nextindice = sufijos[i].indice + k/2; 
            sufijos[i].rango[1] = (nextindice < l)? 
                                  sufijos[idx[nextindice]].rango[0]: -1; 
        } 
  
    // Sort the sufijos according to first k characters 
    std::sort(sufijos, sufijos+l, comparaSufijos);

    this->vs = new int[l]; 
    for (int i = 0; i < l; i++) 
        this->vs[i] = sufijos[i].indice; 
    }
}

void VectorSufijos::print(){
    for (int i = 0; i < numElem; i++) {
        std::cout << vs[i] << " "; 
    }
    std::cout << std::endl; 
}

VectorSufijos::~VectorSufijos(){
    delete(this->cad);
    delete(this->vs);
}

int VectorSufijos::len() const {
    return this->tam;
}

const char * VectorSufijos::operator[](const int idx) const{
    return this->cad+idx;
}