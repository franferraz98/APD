#include <iostream>
#include "hashMap.cpp"
using namespace std;

int main(){
    HashMap<int, int> *h = new HashMap<int,int>(20); 
    h->insert(1,1); 
    h->insert(2,2); 
    h->insert(2,3); 
    h->print(); 
    cout << h->mapSize() <<endl; 
    cout << *h->deleteN(2) << endl; 
    cout << h->mapSize() <<endl; 
    cout << h->isEmpty() << endl; 
    cout << *h->get(2); 
  
    return 0;
}