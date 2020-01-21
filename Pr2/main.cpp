#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"
#include "huffmanCoding.cpp"
#include "tinydir.h"

using namespace std;

double compressionRatio(string s){
    // BURROWS-WHEELER
    string comp = BurrowsWheeler::compress(s.c_str());
    //MTF
    //char *movComp = MoveToFront::compress(comp.c_str(), comp.length());
    //HUFFMAN
    Huffman h1(comp);

	//string huffCod = h1.encode(comp);
    double ratio = (double)((comp.length()+7) / 8)/s.length();

    //HUFFMAN
	//string huffDec = h1.decode(huffCod);    

    //MTF
    //char *movDec = MoveToFront::decompress(huffDec.c_str(), comp.length());
    
    //BURROWS-WHEELER
    string dec = BurrowsWheeler::decompress(comp.c_str());
    if(strcmp(s.c_str(), dec.c_str()) != 0){
        cout << s << endl << endl;
        cout << dec << endl;
        throw;
    }

    //delete(movComp);
    //delete(movDec);
    return ratio;
}

int main(){

    tinydir_dir dir;
    tinydir_open(&dir, "./Tests");
    cout << "FILE; SIZE; RATIO; TIME" << endl;
    while(dir.has_next){
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if(!file.is_dir){
            ifstream ifs(file.path);
            if(ifs.is_open()){
                // Read file to string
                std::stringstream strStream;
                strStream << ifs.rdbuf();
                std::string str = strStream.str();

                // Discard non ASCII chars
                for(int i = 0; i < str.length(); i++){
                    str[i] = max(str[i], ' ');
                }

                auto t1 = std::chrono::high_resolution_clock::now();
                if(file._s.st_size > str.length() + 76){
                    cout << "Difference: " << file._s.st_size << " " << str.length() << endl;
                    cout << str << endl;
                    throw;
                }

                double comp = compressionRatio(str);
                auto t2 = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

                cout <<  file.name << ";" << file._s.st_size << ";" << comp << ";" << time << endl;

                //td::cout << time << std::endl;
            }
            ifs.close();
        }
        tinydir_next(&dir);
    }
    tinydir_close(&dir);

    //cout << "Compression ratio: " << compressionRatio(s) << endl;

    return 0;
}