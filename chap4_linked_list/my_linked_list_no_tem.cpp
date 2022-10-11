#include <iostream>
using namespace std;

class Chain;
class ChainNode {
    friend class Chain;
private:
    int data;
    ChainNode *link;
};

class Chain {
    public:
    Chain() {}
    int Delete();
    bool Delete(int);
    void Insert(int);
    void InsertSorted(int);
};

// Linked list 기본 틀 // 