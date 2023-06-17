#include <iostream>
#include <cassert>

/**
 * @brief Simple binary search tree for integers
 * Tree traversing is done by recursive function and double ** pointers
 */
class CBST{
public:
    CBST(void) : m_Head(nullptr), m_Size(0) {};
    CBST(const CBST & other);
    CBST & operator=(const CBST & other);
    ~CBST();

    bool addNode(int x);
    bool delNode(int x);
    bool isSet(int x);

    void print();

private:
    /**
     * @brief struct representing a single node in a tree
     */
    struct TNode{

        TNode * m_L; /**< Pointer to a node that has smaller value. */
        TNode * m_R; /**< Pointer to a node that has bigger value.  */
        int m_Val;

        TNode(int x) : m_L(nullptr), m_R(nullptr), m_Val(x) {};
        TNode(const TNode & other);
        TNode & operator=(const TNode & other);
        ~TNode();
        TNode * clone() const;
    };
    bool insert(TNode **n, int x);
    bool destroy(TNode **n, int x);

    TNode * m_Head; /**< **/
    size_t m_Size;


    bool find(TNode ** n , int x);
};

CBST::TNode *CBST::TNode::clone() const {

    auto * n = new TNode(m_Val);

    if(m_L){
        n->m_L = m_L -> clone();
    }
    if(m_R){
        n-> m_R = m_R -> clone();
    }
    return n;
}

CBST::TNode::~TNode() {
    delete m_R;
    delete m_L;
}

CBST::TNode::TNode(const CBST::TNode &other) {
    if(other.m_L){
        m_L = other.m_L->clone();
    }
    if(other.m_R){
        m_R = other.m_R->clone();
    }
    m_Val = other.m_Val;
}

CBST::TNode &CBST::TNode::operator=(const CBST::TNode &other) {
    if(this == &other) return *this;

    delete this->m_L;
    delete this->m_R;

    if(other.m_L){
        this->m_L = other.m_L->clone();
    }
    if(other.m_R){
        this->m_R = other.m_R->clone();
    }
    this->m_Val = other.m_Val;

    return *this;
}

CBST::CBST(const CBST &other) : m_Head(other.m_Head ? other.m_Head -> clone() : nullptr),
                                m_Size(other.m_Size) {}

CBST &CBST::operator=(const CBST &other) {
    if(this == &other) return *this;

    delete m_Head;

    this -> m_Head = other.m_Head ? other.m_Head->clone() : nullptr;
    this -> m_Size = other.m_Size;
    return *this;
}

CBST::~CBST() {
    delete m_Head;
}

bool CBST::addNode(int x) {
    if(insert(&m_Head, x)) {
        m_Size++;
        return true;
    }
    else
        return false;
}

/**
 * @param n pointer to a place in a tree (can point to null if there is no node at the moment)
 * @param x value to be added
 * @return successful/unsuccessful adding
 */
bool CBST::insert(CBST::TNode **n, int x) {
    /*  The recursion traverses the tree and finds the position in the tree, where the new value
    * belongs to. However, we shall remember the position "where to put the address of the newly added
    * node". Thus, only the address of the pointer is insufficient, we need to use ** pointer.
    *
    * Please note this works fine for the root node to.
    */

    //found a place to put new value - insert it
    if(!(*n)){
        (*n) = new TNode(x);
        return true;
    }

    //value is already present in the tree
    if((*n)->m_Val == x){
        return false;
    }

    //recursively go further down the tree
    if((*n)->m_Val > x){
        return insert(&((*n)->m_L),x);
    }
    else {
        return insert(&((*n)->m_R),x);
    }
}

void CBST::print() {

}

bool CBST::isSet(int x) {
    return find(&m_Head,x);
}

bool CBST::find(CBST::TNode ** n, int x) {
    if(!(*n)){
        return false;
    }

    if((*n)->m_Val == x){
        return true;
    }

    if((*n)->m_Val > x){
        return find(&((*n)->m_L),x);
    }
    else{
        return find(&((*n)->m_R),x);
    }
}

int main() {
    CBST a;
    assert(a.addNode(1));
    assert(a.addNode(-2));
    assert(a.addNode(100));
    assert(a.addNode(-200));

    assert(!a.addNode(1));
    assert(!a.addNode(-2));

    assert(a.isSet(1));
    assert(a.isSet(-2));
    assert(a.isSet(100));
    assert(a.isSet(-200));
    assert(!a.isSet(3));
    assert(!a.isSet(0));
    return 0;
}
