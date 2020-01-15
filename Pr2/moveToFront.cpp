#include "moveToFront.hpp"

int MoveToFront::indexOf(const char list[256], char c){
    for(int i = 0; i < 256; i++){
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

std::string MoveToFront::compress(const char * c){
    // Crear lista de caracteres inicial
    char list[256];
    for(int i = 0; i < 256; i++){
        list[i] = (char)i;
    }

    std::string res(c);
    for(int i = 0; c[i] != '\0'; i++){
        
        // Buscar indice del caracter
        int idx = indexOf(list, c[i]);

        // Guardar indice en el resultado
        res[i] = (char)idx; 
        //std::cout << idx << ", ";
  
        // Move to front
        moveToFront(list, idx); 
    }
    //std::cout << std::endl;

    return res;

}