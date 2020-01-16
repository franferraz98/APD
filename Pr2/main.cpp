#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"
#include "moveToFront.cpp"

using namespace std;

int main(){
    string s = "I am trying to see if there is a way to quickly convert an 8-bit array of numbers into a 16-bit array of numbers. Basically, I get data from an outside piece of hardware that I need to display on the screen. Right now the data is treated as 8-bit integers, even though I technically need 16-bit integers. What my code does is take two adjacent values and multiplies them, here is an example. And I want to have the program just take 0000101100000011 as its value. I do *not* want to just caste the values into a short, because that will just give me 0000000000000011 and 0000000000001011 and not accomplish anything, as far as I understand.";
    string comp = BurrowsWheeler::compress(s.c_str());
    //cout << comp << endl;

    char *movComp = MoveToFront::compress(comp.c_str(), comp.length());

    char *movDec = MoveToFront::decompress(movComp, comp.length());
    //cout << movDec << endl;

    string dec = BurrowsWheeler::decompress(movDec);
    cout << dec << endl;

    


    return 0;
}