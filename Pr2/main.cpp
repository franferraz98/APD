#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"

using namespace std;

int main(){
    string s = "abaaba";
    string res = BurrowsWheeler::compress(s.c_str());
    cout << res << endl;

    string dec = BurrowsWheeler::decompress(res.c_str());

    cout << dec << endl;

    return 0;
}