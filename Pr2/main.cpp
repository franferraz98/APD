#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"
#include "huffman.cpp"

using namespace std;

int main(){

    string s = "Tomorrow_and_tomorrow_and_tomorrow";
    string comp = BurrowsWheeler::compress(s.c_str());
    //cout << comp << endl;

    char *movComp = MoveToFront::compress(comp.c_str(), comp.length());

    char *movDec = MoveToFront::decompress(movComp, comp.length());
    //cout << movDec << endl;

    string dec = BurrowsWheeler::decompress(movDec);
    cout << dec << endl;

    
    huffman h1("encode.txt", "decode.txt");
	h1.create_pq();
	h1.create_huffman_tree();
	h1.calculate_huffman_codes();
	h1.coding_save();

    huffman h2("decode.txt", "result.txt");
	h2.recreate_huffman_tree();
	h2.decoding_save();

    return 0;
}