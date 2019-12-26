#include "hashMap.hpp"

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    this->value = value; 
    this->key = key; 
}

template<typename K, typename V>
HashMap<K,V>::HashMap(int c){
    //Capacidad inicial de la tabla 
    maxSize = c; 
    size = 0; 
    array = new Node<K,V>*[maxSize];  
    //inicializar todo a nullptr 
    for(int i=0 ; i < maxSize ; i++){
        array[i] = nullptr;
    } 
    //nodo dummy 
    dummyNode = new Node<K,V>(-1, -1);
}

template<typename K, typename V>
int HashMap<K,V>::hash(K key){
    return key % maxSize;
}

template<typename K, typename V>
void HashMap<K,V>::insert(K key, V value){
    Node<K,V> *temp = new Node<K,V>(key, value);  
    // Aplicar funcion hash al indice 
    int index = hash(key); 
        
    // Buscar proximo hueco disponible 
    while(array[index] != nullptr && array[index]->key != key 
            && array[index]->key != -1) { 
        index++; 
        index %= maxSize; 
    }
    // Si se va a insertar nuevo nodo aumentar la capacidad actual
    if(array[index] == nullptr || array[index]->key == -1) {
        size++; 
    }
    array[index] = temp;
}

template<typename K, typename V>
V * HashMap<K,V>::deleteN(int key){
    // Aplicar funcion hash para buscar el indice dada la clave
    int index = hash(key);   
    // Encontrar el nodo con dicha clave
    while(array[index] != nullptr) { 
        // Si se encuentra
        if(array[index]->key == key) { 
            Node<K,V> *temp = array[index];     
            // Insertar dummy 
            array[index] = dummyNode;   
            // Reducir tamaño 
            size--; 
            return &temp->value; 
        } 
        index++; 
        index %= maxSize; 
    } 
        
    // Si no se encuentra
    return nullptr; 
}

template<typename K, typename V>
V * HashMap<K,V>::get(int key) { 
    // Aplicar funcion hash a la clave dada 
    int index = hash(key); 
    int iter=0; 
    // Encontrar el nodo con la clave   
    while(array[index] != nullptr) {   
        int iter =0; 
        if(iter++>maxSize){  // Evitar bucle infinito
            return nullptr;
        }         
        // Devolver el valor si se encuentra 
        if(array[index]->key == key) {
            return &array[index]->value;
        } 
        index++; 
        index %= maxSize; 
    }   
    // Sino devuelve nullptr 
    return nullptr; 
}

template<typename K, typename V>
int HashMap<K,V>::mapSize() { 
    return size; 
} 

template<typename K, typename V>
bool HashMap<K,V>::isEmpty() { 
    return size == 0; 
}

template<typename K, typename V>
void HashMap<K,V>::print() { 
    for(int i=0 ; i<maxSize ; i++) { 
        if(array[i] != nullptr && array[i]->key != -1) 
            std::cout << "key : " << array[i]->key  
                    <<"  value : "<< array[i]->value << std::endl; 
    } 
} 
