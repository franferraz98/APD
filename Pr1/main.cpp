#include "graph.cpp"
#include <random>
#include <chrono>
#include "tinydir.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


#define reps 15

// Driver program to test above functions 
int main() 
{    

    // Use a different seed value for every run. 
            srand(time(NULL)); 

    
    std::cout << "Analizando ficheros..." << std::endl;

    tinydir_dir dir;
    tinydir_open(&dir, "./Tests");
    while(dir.has_next){
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if(!file.is_dir){
            std::cout << file.path << " " << std::flush;

            std::string s = file.path;
            Grafo g(s);
            int N = g.vertices.size();
            std::cout << " N: " << N << std::flush ;

            auto totalTime = 0;
            auto maxTime = 0;
            int bestRes = INT_MAX;
            for(int i = 0; i < reps; i++){
                auto t1 = std::chrono::high_resolution_clock::now();
                int res = g.karger();
                auto t2 = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();

                bestRes = min(res, bestRes);
                maxTime = max(maxTime, time);
                totalTime += time;
            }

            auto avgTime = totalTime / reps;
            

            std::cout << ", Avg: " << avgTime  << "ms Max: " << maxTime << "ms , Cut: " << bestRes << std::endl; 
        }
        tinydir_next(&dir);
    }
    tinydir_close(&dir);

   /* std::string s = "M_prob_0.10_0.txt";
    Grafo g(s);

    // Use a different seed value for every run. 
    srand(time(NULL)); 
  
    printf("\nCut found by Karger's randomized algo is %d\n", 
           g.karger()); 
*/
    return 0; 
} 