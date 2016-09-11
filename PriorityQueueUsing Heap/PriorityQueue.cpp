#include "PriorityQueue.h"
#include <algorithm>

PriorityQueue::PriorityQueue (){
    std::make_heap(v.begin(), v.end());
}

void PriorityQueue :: push(T val){
    v.push_back(val);
    std::push_heap(v.begin(), v.end());
}

T PriorityQueue :: pop(){
    std::pop_heap(v.begin(), v.end());
    T back = v.back();
    v.pop_back();
    return back;
}

bool PriorityQueue :: empty(){
    return v.empty();
}

int PriorityQueue :: size(){
    return v.size();
}

T PriorityQueue :: top(){
    return (v.front());
}
