#include "moveToFront.hpp"

unsigned int MoveToFront::indexOf(const char list[256], char c){
    for(unsigned int i = 0; i < 256; i++){
        if(list[i] == c){
            return i;
        }
    }
    return -1;
}

void MoveToFront::moveToFront(char list[256], int idx){
    char c = list[idx];
    for(int i = idx; i > 0; i--){
        list[i] = list[i-1];
    }
    list[0] = c;
}

char * MoveToFront::compress(const char * c, const int l){
    // Crear lista de caracteres inicial
    char list[256];
    for(unsigned int i = 0; i < 256; i++){
        list[i] = (unsigned char)((i + 32)%256);
    }

    char *res = (char *)malloc(l * sizeof(char));
    for(int i = 0; i < l; i++){
        // Buscar indice del caracter
        unsigned int idx = indexOf(list, c[i]);

        // Guardar indice en el resultado
        res[i] = (unsigned char)(idx) + '#';
  
        // Move to front
        moveToFront(list, idx); 
    }

    return res;
}

char * MoveToFront::decompress(const char * c, const int l){
    // Crear lista de caracteres inicial
    char list[256];
    for(unsigned int i = 0; i < 256; i++){
        list[i] = (unsigned char)((i + 32)%256);
    }

    char *res = (char *)malloc((l+1) * sizeof(char));
    for(int i = 0; i < l; i++){
        // Buscar indice del caracter
        unsigned int idx = (unsigned int)((unsigned char)c[i]-'#');

        // Guardar indice en el resultado
        res[i] = list[idx];
  
        // Move to front
        moveToFront(list, idx); 
    }
    res[l] = '\0';

    return res;
}