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
class Arista{
public:
    Arista(int a, int b);

    // Ids que conecta la arista
    int a, b;
};

class Conjunto{
public:

    // Constructores
    Conjunto(int id);
    Conjunto(std::vector<int> ids);

    // Union de dos conjuntos de vertices
    static Conjunto* combinar(Conjunto *a, Conjunto *b);

    // Union de dos conjuntos de vertices
    Conjunto operator +(Conjunto const &vert);
    // Interseccion de dos conjuntos de vertices
    Conjunto operator *(Conjunto const &vert);

    // ATRIBUTOS
    // Ids que contiene el vertice
    std::vector<int> ids;
};

class Grafo{
public:

    Grafo(int V, int E);

    int karger();

    bool existeArista(Arista a);

    Conjunto* conjuntoQueContiene(int id, int &index);

    // Devuelve false si las aristas pertenecen al mismo conjunto
    bool combinarConjuntos(int id_a, int id_b);

    // Vertices del grafo
    std::vector<Conjunto*> vertices;

    // Aristas del grafo
    std::vector<Arista*> aristas;
};

#endif