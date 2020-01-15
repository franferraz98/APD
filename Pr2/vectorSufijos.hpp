#ifndef VECTORSUFIJOS_HH
#define VECTORSUFIJOS_HH

class VectorSufijos {
protected:
    int * indices;
    char * cad;        
    int tam;


public:
    VectorSufijos(const char * c);
    ~VectorSufijos();
    int len() const;

    void ordenar();
    int indice(int idx) const;

    const char * operator[](const int idx) const;
    const char * sufijo(const int id) const;
};

#endif