#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"
#include "huffman.cpp"

using namespace std;

int main(){

    string s = "Tomorrow_and_tomorrow_and_tomorrow";
    string comp = BurrowsWheeler::compress(s.c_str());
    cout << comp << endl;

    string dec = BurrowsWheeler::decompress(comp.c_str());
    cout << dec << endl;

    string movComp = MoveToFront::compress(comp.c_str());
    cout << movComp << endl;
    
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