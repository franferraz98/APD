#ifndef VECTORSUFIJOS_HH
#define VECTORSUFIJOS_HH

class VectorSufijos {
protected:
    char * cad;        
    int tam;
public:
    VectorSufijos(const char * c);
    ~VectorSufijos();
    int len() const;
    const char * operator[](const int idx) const;
};

#endif