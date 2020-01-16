#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"
#include "huffmanCoding.cpp"

using namespace std;

double compressionRatio(string s){
    // BURROWS-WHEELER
    string comp = BurrowsWheeler::compress(s.c_str());
    //MTF
    char *movComp = MoveToFront::compress(comp.c_str(), comp.length());
    //HUFFMAN
    Huffman h1(movComp);

	string huffCod = h1.encode(movComp);
    double ratio = (double)((huffCod.length()+7) / 8)/s.length();

     //HUFFMAN
	string huffDec = h1.decode(huffCod);    

    //MTF
    char *movDec = MoveToFront::decompress(huffDec.c_str(), comp.length());
    
    //BURROWS-WHEELER
    string dec = BurrowsWheeler::decompress(movDec);
    if(strcmp(s.c_str(), dec.c_str()) != 0){
        throw;
    }
    return ratio;
}

int main(){

    string s = "aaaaaaaaaaaaaaaaa";

    cout << "Compression ratio: " << compressionRatio(s) << endl;

    return 0;
}