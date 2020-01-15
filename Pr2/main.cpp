#include <iostream>
#include <string>
#include "burrowsWheeler.cpp"

using namespace std;

int main(){
    string s = "Tomorrow_and_tomorrow_and_tomorrow$";
    string res = BurrowsWheeler::compress(s.c_str());
    cout << res << endl;

    string dec = BurrowsWheeler::decompress(res.c_str(), s[0]);

    cout << dec << endl;

    return 0;
}