#ifndef _HASH_MAP_
#define _HASH_MAP_

#include <iostream>
//template para tipos genéricos
template<typename K, typename V>

//Nodos del mapa
class Node {
    public: 
    V value; 
    K key; 
      
    //Constructor de los nodos 
    Node(K key, V value);
};

//template para tipos genéricos
template<typename K, typename V>

//Clase HashMap 
class HashMap 
{ 
public:
    //hash element array 
    Node<K,V> **array; 
    int maxSize; 
    //current size 
    int size; 
    //dummy node 
    Node<K,V> *dummyNode;

    HashMap(int c);
    // Implementa la funcion hash para encontrar el indice dada una clave
    int hash(K key);
    // Añade un par clave valor 
    void insert(K key, V value);
    // Borra un par clave valor 
    V * deleteN(int key);
    // Busca el valor de una clave dada 
    V * get(int key);
    // Devuelve el tamaño del hashMap 
    int mapSize();
    // Devuelve cierto si el tamaño es 0 
    bool isEmpty();
    // Presenta por pantalla todos los pares clave valor
    void print();

};

#endif