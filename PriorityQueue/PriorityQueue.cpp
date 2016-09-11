#include "PriorityQueue.h"
#include <algorithm>
#include <iostream>

PriorityQueue::PriorityQueue (){
}

void PriorityQueue :: push(T val){
    //add to back
    v.push_back(val);
    
    int i = v.size() - 1;
    
    //compare to parent until you reach root or order is maintained
    while( (i>0)   &&   (v[i] > v[(i-1)/2]) ){
        //swap
        swap(i, ((i-1)/2) );
        //change i
        i = (i-1)/2 ;
    }
}

T PriorityQueue :: pop(){
    if(v.empty())
        throw "Priority queue is empty";
    int i = 0;
    T max = v[i]; //save highest element to return
    v[i] = v.back(); // replace element 0 (the highest element) with the back element
    v.pop_back(); // remove back element
    
    //now maintain order:
    //Left child = ((i+1)*2) = (i*2) + 1
    //Right child = ((i+1)*2)+1 = (i*2) + 2
    
    //while there are children and one of them is greater than the parent:
    while ( (i*2+1 < v.size()) && ( v[i] < v[(i*2)+1] || v[i] < v[(i*2)+2] ) ){
        int j = (i*2)+1; // left child
        if (v[j] < v[j+1])
            j++; //j will be the greater child
        swap(i, j);
        i = j;
    }
    return max;
}

void PriorityQueue :: swap (int x, int y) {
    //std::cout << "Swapping " << v[x] << " with " << v[y] << std::endl;
    
    T temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

bool PriorityQueue :: empty(){
    return v.empty();
}

int PriorityQueue :: size(){
    return v.size();
}

T PriorityQueue :: top(){
    if(v.empty())
        throw "Priority queue is empty";
    return (v.front());
}
