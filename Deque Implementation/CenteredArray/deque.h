#ifndef DEQUE_H
#define DEQUE_H

#define MIN_DEQUE_CAPACITY 10

#include <iostream>

typedef int EType;

class Deque {
    
public:
    //constructor
    Deque(int capacity = MIN_DEQUE_CAPACITY);
    
    //<< operator
    friend std::ostream &operator <<(std::ostream &os, const Deque &deque);
    
    //insert and remove
    void insert_front (const EType &element);
    EType remove_front();
    void insert_back(const EType &element);
    EType remove_back();
    
    //accessors and mutator
    const EType &getFront()const;
    const EType &getBack()const;
    int getSize() const;
    const EType &getElement (int index) const;
    void setElement (int index, const EType &element);
    
    //searching and sorting
    int find(const EType &element)const;
    bool search(const EType &element)const;
    void sort();
    
private:
    //variables
    int capacity, size;
    EType *array;
    int front, back; //Both start at middle
    
    //functions
    void doubleSize();
    void recenterFront();
    void recenterBack();
    void checkFrontCapacity();
    void checkBackCapacity();
    
};
#endif

