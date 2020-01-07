/**
    Algoritmia para Problemas Dificiles - Pr.1
    graph.hh

    @author Felix Bernal
    @author Francisco Ferraz
    @version 0.1 26/12/2019 
*/
#ifndef GRAPH_HH
#define GRAPH_HH

#include <vector>
#include <string>
#include <memory>

class Arista{
public:
    Arista(int a, int b);

    // Ids que conecta la arista
    int a, b;
};

class Conjunto{
public:

    // Constructor
    Conjunto();

    static std::shared_ptr<Conjunto> padreMayor(std::shared_ptr<Conjunto> p);

    static bool sonIguales(std::shared_ptr<Conjunto> a, std::shared_ptr<Conjunto> b);

    // Union de dos conjuntos de vertices
    static std::shared_ptr<Conjunto> combinar(std::shared_ptr<Conjunto> a, std::shared_ptr<Conjunto> b);

    // Puntero a padre
    std::shared_ptr<Conjunto> parent;
};

class Grafo{
public:

    Grafo(int V, int E);

    Grafo(std::string filename);

    int kargerStein();
    int karger(std::vector<bool> &aristasRestantes, int vertices, int edges);
    int karger();

    bool existeArista(std::shared_ptr<Arista> a);

    std::shared_ptr<Conjunto> conjuntoQueContiene(int id);

    // Devuelve false si las aristas pertenecen al mismo conjunto
    bool combinarConjuntos(int id_a, int id_b);

    // Vertices del grafo
    std::vector<std::shared_ptr<Conjunto>> vertices;

    // Aristas del grafo
    std::vector<std::shared_ptr<Arista>> aristas;

};

#endif