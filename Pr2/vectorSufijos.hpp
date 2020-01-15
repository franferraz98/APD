#ifndef VECTORSUFIJOS_HH
#define VECTORSUFIJOS_HH

struct Sufijo 
{ 
    int indice; // To store original index 
    int rango[2]; // To store ranks and next rank pair 
}; 

class VectorSufijos {
protected:
    char * cad;        
    int tam;
    int * vs;
    int numElem;
public:
    VectorSufijos(const char * c);
    ~VectorSufijos();
    int len() const;
    const char * operator[](const int idx) const;
};

#endif