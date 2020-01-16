#include <string>
#include <map>

using namespace std;


class Huffman{
public:


// The Huffman Tree
struct HuffTreeNode
{
    double p;
    bool leaf;
    char letter;
    
    HuffTreeNode *parent;
    HuffTreeNode *l;
    HuffTreeNode *r;
    
    // nonleaf node
    HuffTreeNode(double p, HuffTreeNode *l, HuffTreeNode *r)
    {
        this -> p = p;
        this -> leaf = false;
        this -> letter = '\0';
        
        this -> parent = NULL;
        this -> l = l;
        this -> r = r;
        l -> parent = this;
        r -> parent = this;
    }
    
    // leaf node
    HuffTreeNode(double p, char c)
    {
        this -> p = p;
        this -> leaf = true;
        this -> letter = c;
        this -> parent = this -> l = this -> r = NULL;
    }
};

// Comparator of two node pointers
struct CmpNodePtrs
{
    // As priority_queue is a max heap rather than min-heap,
    // invert the meaning of the < operator,
    // in order to get lower probabilities at the top
    bool operator()(const HuffTreeNode* lhs, const HuffTreeNode* rhs) const
    {
        return (lhs -> p) > (rhs -> p);
    }
};

    Huffman(string s);
    
    void analyse();
    void build_tree();
    string encode(char c);
    string encode(string s);
    string decode(string s);

protected:
    // The string to analyse
    string str;

    // Maps the encountered characters to their relative frequencies
    map<char, double> P;

    // the root of the tree
    HuffTreeNode *root;

    // mapping each character to its leaf node (for quick encoding)
    map<char, HuffTreeNode*> leaf;
};