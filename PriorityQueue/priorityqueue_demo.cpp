#include "PriorityQueue.h"

#include <iostream>

int main(){
    PriorityQueue pq;
    for (int i=0; i<10; i++)
        pq.push(i);
    
    std::cout<< "the size is now " << pq.size() << std::endl;
    
    int top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    int popped = pq.pop();
    std::cout << popped << " was popped" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;

    
    pq.push(15);
    std::cout << "15 was pushed" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    
    pq.push(11);
    std::cout << "11 was pushed" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    
    pq.push(30);
    std::cout << "30 was pushed" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    
    pq.push(20);
    std::cout << "20 was pushed" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    
    popped = pq.pop();
    std::cout << popped << " was popped" << std::endl;
    top = pq.top();
    std::cout << top << " is at the top" << std::endl;
    
    std::cout << "The size of the priority queue is: " << pq.size() << std::endl;
    
    while (pq.size()>0){
        std::cout << pq.top() << ' ';
        pq.pop();
    }
    if (pq.empty())
        std::cout << std::endl << "The priority queue is empty" << std::endl;
    return 0;
}