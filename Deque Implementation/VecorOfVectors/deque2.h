#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <vector>

#define SUB_VECT_CAPACITY 10

typedef int EType;

class Deque
{
    struct Position{
        int indexPos, subVectPos;
        friend std::ostream &operator <<(std::ostream &os, const Position &pos) {
            os << "[" << pos.indexPos << "] [ " << pos.subVectPos << "]";
            return os;
        }
    };
    friend std::ostream &operator <<(std::ostream &os, const Deque &deque);
public:
    Deque();
    void uninit();
    
    void insert_front(const EType& element);
    void insert_back(const EType& element);
    EType& remove_front();
    EType& remove_back();
    
    
    const EType& getFront() const;
    const EType& getBack() const;
    int getSize() const {return size;}
    const EType& getElement (int index) const;
    void setElement (int index, const EType &element);
    bool empty (){return size==0;}
    
private:
    std::vector <std::vector<EType> *> vec; //a pointer to a vector of pointers to vectors of ETypes
    int size, capacity; //size = how many elements in the deque. capacity = how many subvectors.
    Position front, back;
    
    void checkFrontCapacity();
    void checkBackCapacity();
    void doubleCapacity();
};
#endif


