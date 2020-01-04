#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <chrono>

using namespace std;

#define N 10
#define rep 10

void all1s(ofstream& o, double prob){
    o << N << endl;

    random_device dev;
    mt19937 gen(dev());
    uniform_real_distribution<double> distrib(0.0,1.0);

    char mat[N][N];

    for(int i=0; i<N; i++){
        for(int j=i; j<N; j++){
            double rand = distrib(gen);
            if(rand<prob || i==j){
                mat[i][j] = '1';
            } else {
                mat[i][j] = '0';
            }
            mat[j][i] = mat[i][j];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            o << mat[i][j];
        }
        o << endl;
    }
}

void oneColumn(ofstream& o, int prod){
    o << N << endl;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i == prod || j== prod || i==j){
                o << '1';
            } else {
                o << '0';
            }
        }
        o << endl;
    }
}

int main(){
    auto t1 = chrono::high_resolution_clock::now();
    
    /* General */

    for(double prob = 0.1; prob<=0.9; prob += 0.1){
        for(int i=0; i<rep; i++){
            string p = to_string(prob).substr(0,4);
            string filename = "M_prob_" + p + "_" + to_string(i) + ".txt"; 
            ofstream o(filename, ios::trunc);
            if(o.is_open()){
                all1s(o,prob);
            }
            o.close();
        }
    }

    /* All ones */

    string p = to_string(1.0).substr(0,4);
    string filename = "M_prob_" + p + "_" + to_string(0) + ".txt";
    ofstream o(filename, ios::trunc);
    if(o.is_open()){
        all1s(o,1.0);
    }
    
    o.close();

    /* All zeroes */

    p = to_string(0.0).substr(0,4);
    filename = "M_prob_" + p + "_" + to_string(0) + ".txt";
    o = ofstream(filename, ios::trunc);
    if(o.is_open()){
        all1s(o,0.0);
    }
    o.close();
    auto t2 = chrono::high_resolution_clock::now();

    auto time = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    /* One product connected to all */

    int numColAll = 10;
    for(int i=0; i<numColAll; i++){
        filename = "M_prodAll_" + to_string(i) + ".txt"; 
        o = ofstream (filename, ios::trunc);

        int prod = i * (N-1) / (numColAll-1);
        if(o.is_open()){
            oneColumn(o,prod);
        }
        o.close();
    }

    cout << "Time elapsed: " << time << "ms" << endl;

}