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
    size_t getSize();

    friend std::ostream & operator << (std::ostream &, const CBST &);

private:
    /**
     * @brief struct representing a single node in a tree
     */
    struct TNode{
    public:


        TNode * m_L; /**< Pointer to a node that has smaller value. */
        TNode * m_R; /**< Pointer to a node that has bigger value.  */
        int m_Val;

        TNode(int x) : m_L(nullptr), m_R(nullptr), m_Val(x) {};
        TNode(const TNode & other);
        TNode & operator=(const TNode & other);
        ~TNode();
        TNode * clone() const;
        void print(std::ostream &, bool) const;
    };
    bool insert(TNode **n, int x);
    bool destroy(TNode **n, int x);

    TNode * m_Head; /**< Highest node**/
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

void CBST::TNode::print(std::ostream & os, bool first) const {
    if(m_L){
        m_L->print(os, first);
        first = false;
    }

    if(!first) os << ", ";
    os << m_Val;

    if(m_R){
        m_R->print(os, false);
    }


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

bool CBST::isSet(int x) { /**< return true if there is x value in the one of the nodes, false if there is no such value */
    return find(&m_Head,x);
}


bool CBST::find(CBST::TNode ** n, int x) { /**< recursive function that finds a value for a isSet function */
    if(!(*n)){ //reached end of the tree, no needed value.
        return false;
    }

    if((*n)->m_Val == x){ //found
        return true;
    }

    //not found - traverse further
    if((*n)->m_Val > x){
        return find(&((*n)->m_L),x);
    }
    else{
        return find(&((*n)->m_R),x);
    }
}

bool CBST::delNode(int x) { /**< deletes a node with x value using recursive destroy function */
    if(destroy(&m_Head, x)){
        m_Size--;
        return true;
    }
    else return false;
}

bool CBST::destroy(CBST::TNode **n, int x) {
    if(!(*n)) return false; //Reached end of the tree, no needed value.

    if((*n)->m_Val == x){ //Found node to delete
        TNode * toDestroy = (*n);

        if((*n)->m_L && (*n)->m_R) { //Node has two children
            //Go to the left node and find the rightmost node from it. We need to find value of the rightmost node and
            //set this rightmost value in the node we want to delete and then delete the rightmost node
            //that way we will assure that we have deleted needed value but still have correct pointers m_L and m_R
            n = &((*n)->m_L);
            while ((*n)->m_R) {
                n = &(*n)->m_R;
            }
            toDestroy->m_Val = (*n)->m_Val;
            toDestroy = (*n);
        }

        if((*n)->m_L) { //node has one smaller child
            (*n)=(*n)->m_L;
        }
        else //node has one greater child
            (*n)=(*n)->m_R;

        //set all children to nullptr so destructor do not recursively delete data we need
        toDestroy->m_L = toDestroy->m_R = nullptr;
        delete toDestroy;
        return true;
    }

    if((*n)->m_Val > x) return destroy(&(*n)->m_L, x);
    else return destroy(&(*n)->m_R, x);
}

size_t CBST::getSize() {
    return m_Size;
}

std::ostream &operator<<(std::ostream & os, const CBST & a) {
    os << "[";
    a.m_Head->print(os,true);
    os << "]";
    return os;
}


int main() {
    CBST a;
    assert(a.addNode(100));
    assert(a.addNode(50));
    assert(a.addNode(200));
    assert(a.addNode(175));
    assert(a.addNode(300));
    assert(a.addNode(199));
    assert(a.addNode(301));
    assert(a.addNode(10));
    assert(a.addNode(5));
    assert(a.addNode(60));
    assert(a.addNode(55));
    assert(a.addNode(70));


    std::cout << "Before deletion: ";
    std::cout << a << std::endl;
    std::cout << "Size before: " << a.getSize() << std::endl;

    assert(!a.addNode(5));
    assert(!a.addNode(70));
    assert(!a.addNode(301));

    assert(a.isSet(100));
    assert(a.isSet(50));
    assert(a.isSet(200));
    assert(a.isSet(175));
    assert(a.isSet(300));
    assert(a.isSet(199));
    assert(a.isSet(301));
    assert(a.isSet(10));
    assert(a.isSet(5));
    assert(a.isSet(60));
    assert(a.isSet(55));
    assert(a.isSet(70));

    assert(!a.isSet(3));
    assert(!a.isSet(0));

    assert(a.delNode(10));
    assert(a.delNode(200));
    assert(a.delNode(300));

    assert(!a.delNode(300));
    assert(!a.delNode(999));

    assert(a.isSet(100));
    assert(a.isSet(50));
    assert(a.isSet(175));
    assert(a.isSet(199));
    assert(a.isSet(301));
    assert(a.isSet(5));
    assert(a.isSet(60));
    assert(a.isSet(55));
    assert(a.isSet(70));
    assert(!a.isSet(10));
    assert(!a.isSet(200));
    assert(!a.isSet(300));

    std::cout << "After deletion:  ";
    std::cout << a << std::endl;
    std::cout << "Size after: "  << a.getSize() << std::endl;

    return 0;
}
