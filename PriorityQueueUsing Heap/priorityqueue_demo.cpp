#include "PriorityQueue.h"

#include <iostream>

int main(){
    PriorityQueue pq;
    for (int i=10; i>0; i--)
        pq.push(i);
    int top = pq.top();
    std::cout << top << std::endl;
    pq.pop();
    top = pq.top();
    std::cout << top << std::endl;
    return 0;
}