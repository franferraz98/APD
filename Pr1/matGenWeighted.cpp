#include <cstdio>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <chrono>

#define N 100

using namespace std;

int** create2DArray(unsigned height, unsigned width)
{
    random_device dev;
    mt19937 gen(dev());
    uniform_int_distribution<int> distrib(0,10);
    int** array2D = 0;
    array2D = new int*[height];

    for (int h = 0; h < height; h++) {
        array2D[h] = new int[width];
    }

    for (int h = 0; h < height; h++) {

        for (int w = h; w < width; w++) {
            int rand = distrib(gen);
            array2D[h][w] = rand;
            array2D[w][h] = rand;
        }
    }

    return array2D;
}

int main(){

    auto t1 = chrono::high_resolution_clock::now();

    int** my2DArray = create2DArray(N, N);

    string filename = "Tests/pesos.txt";
    ofstream o(filename, ios::trunc);

    o << std::to_string(N) << "\n";
    for (int h = 0; h < N; h++)
    {
        for (int w = 0; w < N; w++)
        {
            o << (unsigned char)('0' + my2DArray[h][w]%10);
        }
        o << '\n';
    }

    o << "\0";

    // important: clean up memory
    printf("\n");
    printf("Cleaning up memory...\n");
    for (int  h = 0; h < N; h++)
    {
    delete [] my2DArray[h];
    }
    delete [] my2DArray;
    my2DArray = 0;
    printf("Ready.\n");

    auto t2 = chrono::high_resolution_clock::now();

    auto time = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();

    cout << "Time elapsed: " << time << "ms" << endl;

    return 0;
}