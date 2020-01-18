/*
 Petar 'PetarV' Velickovic
 Algorithm: Huffman Coding
*/

#include "huffmanCoding.hpp"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The Huffman coding scheme assigns a variable-length prefix code to each character
 in a given set of characters, constructing an optimal lossless coding scheme with
 respect to the character distribution's entropy.
 
 The version implemented here analyses a given ASCII character string in order to
 obtain optimal codes based on character frequencies in the string. A more general
 version would receive a probability distribution instead.
 
 Complexity:    O(n) time to construct
                O(H) time (on average) to encode/decode, where H is the entropy
*/






// Produces the probability distribution (may be omitted if known in advance)
inline void Huffman::analyse()
{
    for (int i=0;i<str.length();i++)
    {
        P[str[i]]++;
    }
    for (auto it = P.begin();it!=P.end();it++)
    {
        P[it -> first] = it -> second / str.length();
    }
}

// Construct the Huffman Tree using the probability distribution
inline void Huffman::build_tree()
{
    priority_queue<HuffTreeNode*, vector<HuffTreeNode*>, CmpNodePtrs> pq;
    
    // First construct the leaves, and fill the priority queue
    for (auto it = P.begin();it!=P.end();it++)
    {
        leaf[it -> first] = new HuffTreeNode(it -> second, it -> first);
        pq.push(leaf[it -> first]);
    }
    
    while (pq.size() > 1)
    {
        HuffTreeNode* L = pq.top(); pq.pop();
        HuffTreeNode* R = pq.top(); pq.pop();
        
        // Spawn a new node generating the children
        HuffTreeNode* par = new HuffTreeNode((L -> p) + (R -> p), L, R);
        pq.push(par);
    }
    
    root = pq.top(); pq.pop();
}

// Huffman-encode a given character
inline string Huffman::encode(char c)
{
    string ret = "";
    
    HuffTreeNode* curr = leaf[c];
    while (curr -> parent != NULL)
    {
        if (curr == curr -> parent -> l) ret += "0";
        else if (curr == curr -> parent -> r) ret += "1";
        
        curr = curr -> parent;
    }
    
    reverse(ret.begin(), ret.end());
    return ret;
}

// Huffman-encode the given string
inline string Huffman::encode(string s)
{
    string ret = "";
    
    for (int i=0;i<s.length();i++)
    {
        ret += encode(s[i]);
    }
    
    return ret;
}

// Huffman-decode the given string
inline string Huffman::decode(string s)
{
    string ret = "";
    
    int i = 0;
    HuffTreeNode* curr;
    
    while (i < s.length())
    {
        curr = root;
        while (!(curr -> leaf))
        {
            if (s[i++] == '0') curr = curr -> l;
            else curr = curr -> r;
        }
        ret += curr -> letter;
    }
    return ret;
}

Huffman::Huffman(string s) : str(s){
    analyse();
    build_tree();
}

Huffman::~Huffman(){
    delete(this->root);
}
