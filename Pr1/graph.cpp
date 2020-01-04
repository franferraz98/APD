/**
    Algoritmia para Problemas Dificiles - Pr.1
    graph.cpp

    @author Felix Bernal
    @author Francisco Ferraz
    @version 0.1 26/12/2019 
*/
#include "graph.hpp"
#include <iostream>
#include <algorithm> //std::find
#include <random>

Arista::Arista(int a, int b): a(a), b(b){

}

Conjunto::Conjunto(int id): ids({id}){

}

Conjunto::Conjunto(std::vector<int> ids): ids({}){
    for(int id : ids){
        this->ids.push_back(id);
    }
}

Conjunto* Conjunto::combinar(Conjunto *a, Conjunto *b){
    Conjunto *res = new Conjunto(a->ids);
    for(int id : b->ids){
        res->ids.push_back(id);
    }
    
    return res;
}

Conjunto Conjunto::operator +(Conjunto const &vert){
    Conjunto res(this->ids);
    for(int id : vert.ids){
        res.ids.push_back(id);
    }
    
    return res;
}

Conjunto Conjunto::operator *(Conjunto const &vert){
    Conjunto res({});

    for(int a : vert.ids){
        for(int b : this->ids){
            if(a == b){
                res.ids.push_back(a);
            }
        }
    }
    
    return res;
}

template <typename T>
bool vectorContiene(std::vector<T> v, T x){
    if(std::find(v.begin(), v.end(), x) != v.end()) {
        return true;
    } else {
        return false;
    }
}


Grafo::Grafo(int VERT_NUM, int EDGES_NUM){
    // initial vertices list
    for(int i = 0; i < VERT_NUM; i++){
        std::cout << "Agregando vertice " << i+1 << std::endl;
        Conjunto *vert = new Conjunto(i+1);
        this->vertices.push_back(vert);
    }

    //Generate random graph
    for(int i = 0; i < EDGES_NUM; i++){
        std::cout << "Agregando arista " << i+1 << std::endl;
        bool exists = true;
        while(exists){
            // Generate random edge
            int a = rand() % VERT_NUM + 1; //1 to V
            int b;
            do{
                b = rand() % VERT_NUM + 1; // 1 to V
            }while(b == a);// loops not allowed (a -> a)
            Arista *arista = new Arista(a, b);

            //Check that edge doesnt exist already
            exists = existeArista(*arista);

            //If edge does not exist, add to edges list
            if(!exists){
                std::cout << arista->a << ", " << arista->b << std::endl;
                aristas.push_back(arista);
            }
        }
    }
}

bool Grafo::existeArista(Arista a){
    for(auto b : aristas){
        if((a.a == b->a && a.b == b->b) || (a.a == b->b && a.b == b->a)){
            return true;
        }
    }
    return false;
}

Conjunto* Grafo::conjuntoQueContiene(int id, int &i){
    i = 0;
    for(Conjunto *c : this->vertices){
        if(vectorContiene(c->ids, id)){
            return c;
        }
        i++;
    }
    return nullptr;
}

bool Grafo::combinarConjuntos(int id_a, int id_b){
    int i_a, i_b;
    std::cout << "buscar " << id_a << ", " << id_b << std::endl;
    Conjunto *c_a = conjuntoQueContiene(id_a, i_a);
    Conjunto *c_b = conjuntoQueContiene(id_b, i_b);

    if(c_a != nullptr && c_b != nullptr){
        
        if(i_a != i_b){
            // Combinar los dos conjunto en uno y agregarlo al grafo
            Conjunto *c_nuevo = Conjunto::combinar(c_a, c_b);

            
            this->vertices.push_back(c_nuevo);

            // Eliminar los conjuntos anteriores
            if(i_b < i_a)
            std::swap(i_a, i_b);

            vertices.erase(vertices.begin() + i_a);
            vertices.erase(vertices.begin() + i_b-1);

            return true;
        }else{
            std::cout << "Mismo conjunto" << std::endl;
            // Vertices estan en el mismo conjunto
            return false;
        }
    }else{
        std::cout << "FALLO nullptr" << std::endl;
        // Alguno de los vertices no se ha encontrado
        return false;
    }
}

int Grafo::karger(){
    // Get data of given graph 
    int V = this->vertices.size();
    int E = this->aristas.size();
  
    // Initially there are V vertices in 
    // contracted graph 
    int vertices = V; 
  
    // Keep contracting vertices until there are 
    // 2 vertices. 
    while (vertices > 2) 
    {
        // Pick a random edge 
        int i = rand() % E; 
        
        
        if(this->combinarConjuntos(aristas[i]->a, aristas[i]->b)){
            std::cout << "Combinando (" << aristas[i]->a << ", " << aristas[i]->b << ")" << std::endl;
            vertices--;
        }
    } 
  
    // Now we have two vertices (or subsets) left in 
    // the contracted graph, so count the edges between 
    // two components and return the count. 
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int i_1, i_2;
        Conjunto* conjunto1 = conjuntoQueContiene(aristas[i]->a, i_1);
        Conjunto* conjunto2 = conjuntoQueContiene(aristas[i]->b, i_2);
        std::cout << aristas[i]->a << ", " << aristas[i]->b << ": " << i_1 << ", " << i_2 << std::endl;
        if (i_1 != i_2)
          cutedges++;
    }
  
    return cutedges; 
}

