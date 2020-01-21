#ifndef VECTORSUFIJOS_HH
#define VECTORSUFIJOS_HH

#define EOF_CHAR 3

struct Sufijo 
{ 
    int indice; // To store original index 
    int rango[2]; // To store ranks and next rank pair 
}; 

class VectorSufijos {
protected:
    int * indices;
    char * cad;        
    int tam;


public:
    VectorSufijos(const char * c);
    ~VectorSufijos();
    int len() const;

    void print();
    void radix(const int col, const int j_0, const int j_f);
    void ordenar();
    int indice(int idx) const;

    const char * operator[](const int idx) const;
    const char * sufijo(const int id) const;
};

#endif