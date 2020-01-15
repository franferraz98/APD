#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"

using namespace std;

int main(){
    string s = "Tomorrow_and_tomorrow_and_tomorrow";
    string comp = BurrowsWheeler::compress(s.c_str());
    cout << comp << endl;

    string dec = BurrowsWheeler::decompress(comp.c_str());
    cout << dec << endl;

    string movComp = MoveToFront::compress(comp.c_str());
    cout << movComp << endl;

    


    return 0;
}