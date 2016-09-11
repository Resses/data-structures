#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include "deque.h"

using namespace std;

//CONSTRUCTOR:

//the min capacity for the deque will be 10
Deque::Deque(int capacity):capacity(max(capacity, MIN_DEQUE_CAPACITY)),size(0), array(new EType[capacity]), front(capacity/2), back((capacity/2)-1)
{
    cout << "Deque created with capacity: " << capacity << " size: " << size << " front: " << front << " back: " <<back <<endl;
}

// << operator

std::ostream &operator <<(std::ostream &os, const Deque &deque) {
    os << "F: " << deque.front << " B: " << deque.back << " ... ";
    os << '{';
    if(deque.empty())
        os << " }";
    else{
        int i = deque.front;
        while (i!=deque.back){
            os << deque.array[i] << ", ";
            i++;
            if(i==deque.capacity)
                i = 0;
        }
        os << deque.array[deque.back] << "}";
    }
    return os;
}

//PRIVATE:

//capacity management:


void Deque::checkCapacity(){
    if(size == capacity){
        int oldCapacity = capacity;
        capacity*=2;
        EType *temp = new EType[capacity];
        for (int i = 0; i < size; i++){
            temp[i] = array[front];
            front ++ ;
            if (front == oldCapacity)
                front = 0;
        }
        front = 0;
        back = size-1;
        delete[]array;
        array = temp;
        cout << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
    }
}

//PUBLIC:

//insert and remove:

void Deque::insert_front(const EType &element){
    checkCapacity();
    front --;
    if(front<0)
        front = capacity - 1;
    array[front] = element;
    size ++;
}

EType Deque::remove_front() {
    if(size<=0){
        ostringstream oss;
        oss << "remove_front - cannot remove_front on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = array[front];
    front++;
    if(front == capacity)
        front = 0;
    size --;
    return removedElement;
}

void Deque::insert_back(const EType &element) {
    checkCapacity();
    back++;
    if(back == capacity)
        back = 0;
    array[back] = element;
    size ++;
}

EType Deque::remove_back(){
    if(size<=0){
        ostringstream oss;
        oss << "remove_back - cannot remove_back on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = array[back];
    back--;
    if(back<0)
        back = capacity -1;
    size--;
    return removedElement;
}

//Accessors and mutator:

const EType& Deque::getFront() const {
    if (size == 0){
        ostringstream oss;
        oss << "the array is empty";
        throw oss.str();
    }
    return array[front];
}

const EType& Deque::getBack() const {
    if (size==0){
        ostringstream oss;
        oss << "the array is empty";
        throw oss.str();
    }
    return array[back];
}

int Deque::getSize() const {return size;}

const EType& Deque::getElement (int index) const {
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "getElement - out of bounds index (" << index << ") for array with size" << size;
        throw oss.str();
    }
    return array[(front+index)%capacity];
}

void Deque::setElement (int index, const EType &element){
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "setElement - out of bounds index (" << index << ") for array of size " << size;
        throw oss.str();
    }
    array[(front+index)%capacity] = element;
    return;
}

bool Deque::empty() const{
    if(size == 0)
        return true;
    else
        return false;
}
