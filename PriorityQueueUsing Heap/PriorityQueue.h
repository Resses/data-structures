#ifndef ____PriorityQueue__
#define ____PriorityQueue__

#include <vector>

typedef int T;

class PriorityQueue {
public:
    PriorityQueue();
    
    void push(T val); //insert element
    T pop(); //remove element
    
    bool empty();
    int size();
    T top();
    
private:
    std::vector<T> v;
};

#endif
