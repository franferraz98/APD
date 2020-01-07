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
#include <memory>
#include <random>
#include <fstream>
#include <string>

Arista::Arista(int a, int b): a(a), b(b){

}

Conjunto::Conjunto(): parent(nullptr){

}

std::shared_ptr<Conjunto> Conjunto::padreMayor(std::shared_ptr<Conjunto> p){
    while(p->parent != nullptr){
        p = p->parent;
    }
    return p;
}

bool Conjunto::sonIguales(std::shared_ptr<Conjunto> a, std::shared_ptr<Conjunto> b){
    return padreMayor(a) == padreMayor(b);
}

std::shared_ptr<Conjunto> Conjunto::combinar(std::shared_ptr<Conjunto> a, std::shared_ptr<Conjunto> b){
    std::shared_ptr<Conjunto> res = std::make_shared<Conjunto>();
    padreMayor(a)->parent = res;
    padreMayor(b)->parent = res;
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
    this->vertices.resize(VERT_NUM);
    // initial vertices list
    for(int i = 0; i < VERT_NUM; i++){
        //std::cout << "Agregando vertice " << i+1 << std::endl;
        std::shared_ptr<Conjunto> vert = std::make_shared<Conjunto>();
        this->vertices[i] = vert;
    }

    //Generate random graph
    for(int i = 0; i < EDGES_NUM; i++){
        //std::cout << "Agregando arista " << i+1 << std::endl;
        bool exists = true;
        while(exists){
            // Generate random edge
            int a = rand() % VERT_NUM + 1; //1 to V
            int b;
            do{
                b = rand() % VERT_NUM + 1; // 1 to V
            }while(b == a);// loops not allowed (a -> a)
            std::shared_ptr<Arista> arista = std::make_shared<Arista>(a, b);

            //Check that edge doesnt exist already
            exists = existeArista(arista);

            //If edge does not exist, add to edges list
            if(!exists){
                //std::cout << arista->a << ", " << arista->b << std::endl;
                aristas.push_back(arista);
            }
        }
    }
}


Grafo::Grafo(std::string filename){
    std::ifstream ifs(filename);
    if(ifs.is_open()){

        std::string s;
        getline(ifs,s);

        int N = stoi(s);
        //std::cout << "Dimensions: " << N << std::endl;

        int ** mat = 0;
        mat = new int*[N];

        for (int h = 0; h < N; h++) {
            mat[h] = new int[N];
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j<N; j++){
                // Leer caracter (1 o 0)
                char c = ifs.get();

                // Saltar espacios, tabuladores, saltos de linea...
                while(c == ' ' || c == '\n' || c == '\t'){
                    c = ifs.get();
                }


                mat[i][j] = c - '0';
            }
        }

        this->vertices.resize(N);
        // initial vertices list
        for(int i = 0; i < N; i++){
            //std::cout << "Agregando vertice " << i+1 << std::endl;
            std::shared_ptr<Conjunto> vert = std::make_shared<Conjunto>();
            this->vertices[i] = vert;
        }

        // edges list
        aristas = {};
        for(int i = 0; i < N; i++){
            for(int j = 0; j <= i; j++){
                
                // Add edge as many times as indicated
                for(int k = 0; k < mat[i][j]; k++){
                    if( i != j){
                        std::shared_ptr<Arista> arista = std::make_shared<Arista>(i+1, j+1);
                        //Add to edges list
                        //std::cout << arista->a << ", " << arista->b << std::endl;
                        aristas.push_back(arista);
                    }
                    
                }
            }
        }
    }
}

bool Grafo::existeArista(std::shared_ptr<Arista> a){
    for(auto b : aristas){
        if((a->a == b->a && a->b == b->b) || (a->a == b->b && a->b == b->a)){
            return true;
        }
    }
    return false;
}

std::shared_ptr<Conjunto> Grafo::conjuntoQueContiene(int id){
    return vertices[id-1];
}

bool Grafo::combinarConjuntos(int id_a, int id_b){
    //int i_a, i_b;
    //std::cout << "buscar " << id_a << ", " << id_b << std::endl;
    /* std::shared_ptr<Conjunto> c_a = conjuntoQueContiene(id_a, i_a);
    std::shared_ptr<Conjunto> c_b = conjuntoQueContiene(id_b, i_b); */

    std::shared_ptr<Conjunto> c_a = conjuntoQueContiene(id_a);
    std::shared_ptr<Conjunto> c_b = conjuntoQueContiene(id_b);

    if(c_a != nullptr && c_b != nullptr){
        
        if(!Conjunto::sonIguales(c_a, c_b)){
            // Combinar los dos conjunto en uno y agregarlo al grafo
            std::shared_ptr<Conjunto> c_nuevo = Conjunto::combinar(c_a, c_b);

            this->vertices[id_a-1] = c_nuevo;
            this->vertices[id_b-1] = c_nuevo;
             
            // Eliminar los conjuntos anteriores
            /* if(_b < i_a)
            std::swap(i_a, i_b);

            vertices.erase(vertices.begin() + i_a);
            vertices.erase(vertices.begin() + i_b-1); */

            return true;
        }else{
            //std::cout << "Mismo conjunto" << std::endl;
            // Vertices estan en el mismo conjunto
            return false;
        }
    }else{
        std::cout << "FALLO nullptr" << std::endl;
        // Alguno de los vertices no se ha encontrado
        return false;
    }
}

int Grafo::kargerStein(){
    //std::cout << "Adios" << std::endl;
    // Get data of given graph 
    int V = this->vertices.size();
    int E = this->aristas.size();
  
    // Initially there are V vertices in 
    // contracted graph 
    std::vector<bool> aristasKarger;
    aristasKarger.resize(E,false);

    int edges = E;
    int vertices = V; 

    int steinLimit = V/sqrt(2);
    
    // Keep contracting vertices until there are 
    // 2 vertices. 
    while (vertices > steinLimit && edges >= 1) 
    {
        // Pick a random edge 
        int i = rand() % E; 
        while(aristasKarger[i]){
            //std::cout << "Hola: " << i << std::endl;
            i = (i+1)%E;
        }

        if(this->combinarConjuntos(aristas[i]->a, aristas[i]->b)){
            //std::cout << "Combinando (" << aristas[i]->a << ", " << aristas[i]->b << ")" << std::endl;
            vertices--;
        }
        

        //Eliminar ocurrencias de la arista
        aristasKarger[i] = true;
        int b_i = i;
        while(b_i > 0 && aristas[i]->a == aristas[b_i-1]->a && aristas[i]->b == aristas[b_i-1]->b){
            b_i--;
            aristasKarger[b_i] = true;
        }
        int e_i = i;
        while(e_i < edges-1 && aristas[i]->a == aristas[e_i+1]->a && aristas[i]->b == aristas[e_i+1]->b){
            e_i++;
            aristasKarger[e_i] = true;
        }

        edges -= e_i - b_i + 1;
    }
  
    // Copy current graph and apply karger twice, get best result
    Grafo g2(*this);
    g2.vertices = this->vertices;
    g2.aristas = this->aristas;
    std::vector<bool> aristasKargerAux = aristasKarger;
    int res2 = g2.karger(aristasKargerAux, vertices, edges);

    int res1 = this->karger(aristasKarger, vertices, edges);

    if(res1 < res2){
        return res1;
    }else{
        this->vertices = g2.vertices;
        this->aristas = g2.aristas;

        return res2;
    }
}

int Grafo::karger(std::vector<bool> &aristasKarger, int vertices, int edges){

    //std::cout << "Hola" << std::endl;
    // Get data of given graph 
    int V = this->vertices.size();
    int E = this->aristas.size();
  
    // Initially there are V vertices in 
    // contracted graph 
    //int edges = E;
    //int vertices = V;

    // Keep contracting vertices until there are 
    // 2 vertices. 
    while (vertices > 2 && edges >= 1) 
    {
        // Pick a random edge 
        int i = rand() % E; 
        while(aristasKarger[i]){
            //std::cout << "Hola: " << i << std::endl;
            i = (i+1)%E;
        }

        if(this->combinarConjuntos(aristas[i]->a, aristas[i]->b)){
            //std::cout << "Combinando (" << aristas[i]->a << ", " << aristas[i]->b << ")" << std::endl;
            vertices--;
        }
        

        //Eliminar ocurrencias de la arista
        aristasKarger[i] = true;
        int b_i = i;
        while(b_i > 0 && aristas[i]->a == aristas[b_i-1]->a && aristas[i]->b == aristas[b_i-1]->b){
            b_i--;
            aristasKarger[b_i] = true;
        }
        int e_i = i;
        while(e_i < edges-1 && aristas[i]->a == aristas[e_i+1]->a && aristas[i]->b == aristas[e_i+1]->b){
            e_i++;
            aristasKarger[e_i] = true;
        }

        edges -= e_i - b_i + 1;
        //edges--;
    } 
  
    // Now we have two vertices (or subsets) left in 
    // the contracted graph, so count the edges between 
    // two components and return the count. 
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        std::shared_ptr<Conjunto> conjunto1 = this->vertices[(aristas[i]->a) -1];
        std::shared_ptr<Conjunto> conjunto2 = this->vertices[(aristas[i]->b) -1];
        //std::cout << aristas[i]->a << ", " << aristas[i]->b << ": " << i_1 << ", " << i_2 << std::endl;
        if (!Conjunto::sonIguales(conjunto1, conjunto2))
          cutedges++;
    }
  
    return cutedges; 
}

int Grafo::karger(){
    std::vector<bool> aristasKarger;
    aristasKarger.resize(this->aristas.size(),false);
    return this->karger(aristasKarger, this->vertices.size(), this->aristas.size());
}

