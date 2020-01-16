#include <iostream>
#include <fstream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"
#include "huffmanCoding.cpp"
#include "tinydir.h"

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

    delete(movComp);
    delete(movDec);
    return ratio;
}

int main(){

    tinydir_dir dir;
    tinydir_open(&dir, "./Tests");
    while(dir.has_next){
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if(!file.is_dir){
            string text = "";
            string s = file.path;
            ifstream ifs(s);
            if(ifs.is_open()){
                while(!ifs.eof()){
                    string line;
                    getline(ifs,line);
                    text += line;
                }
                cout <<  file.name << ";" << file._s.st_size << ";" << compressionRatio(s) << endl;
            }
            ifs.close();
        }
        tinydir_next(&dir);
    }
    tinydir_close(&dir);

    //cout << "Compression ratio: " << compressionRatio(s) << endl;

    return 0;
}