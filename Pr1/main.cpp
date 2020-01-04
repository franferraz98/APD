#include "graph.cpp"
#include <random>
#include <chrono>

// Driver program to test above functions 
int main() 
{    
    int V = 5;  // Number of vertices in graph 
    int E = 10;  // Number of edges in graph 
    //Grafo g(V, E);

    std::string s = "M_prob_0.10_0.txt";
    Grafo g(s);

    // Use a different seed value for every run. 
    srand(time(NULL)); 
  
    printf("\nCut found by Karger's randomized algo is %d\n", 
           g.karger()); 

    return 0; 
} 