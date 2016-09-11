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
    if(deque.getSize() == 0)
        os << " }";
    else{
        for (int i = deque.front; i<=deque.back; i++)
            os << deque.array[i] << (i < deque.back ? ", " : "");
        os << "}";
    }
    return os;
}

//PRIVATE:

//capacity management:

void Deque::doubleSize(){
    int oldCapacity = capacity;
    capacity*=2;
    EType *temp = new EType[capacity];
    int mid = capacity / 2;
    int start = mid - (size/2);
    int end = start + size - 1;
    for (int i = start; i <= end; i++)
            temp[i] = array[front++];
    front = start;
    back = start + size-1;
    delete[]array;
    array = temp;
    cout << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
}

void Deque::recenterFront(){
    int mid = capacity / 2;
    int end = mid + (size/2);
    int start = end - (size-1);
    for (int i = end; i >= start; i--){
        array[i] = array[back];
        back --;
    }
    front = start;
    back = end;
    cout << "array was recentered. F: " << front << " B: " << back;
    cout << " size: " << size << endl;
}

void Deque::recenterBack(){
    int mid = capacity / 2;
    int start = mid - (size/2);
    int end = start + size-1;
    for (int i = start; i <= end; i++){
        array[i] = array[front];
        front ++;
    }
    front = start;
    back = end;
    cout << "array was recentered. F: " << front << " B: " << back;
    cout << " size: " << size << endl;
}

void Deque::checkFrontCapacity(){
    if(front == 0){ //Left Capacity is full.
        if (size >= capacity-2){    //There are only 2 spots left... Get a bigger array
            doubleSize();
        }
        else
            recenterFront();
    }
}

void Deque::checkBackCapacity(){
    if(back == capacity-1){
        if (size >= capacity-2){    //There are only 2 spots left... Get a bigger array
            doubleSize();
        }
        else
            recenterBack();
    }
}

//PUBLIC:

//insert and remove:

void Deque::insert_front(const EType &element){
    checkFrontCapacity();
    array[--front] = element;
    size ++;
}

EType Deque::remove_front() {
    if(size<=0){
        ostringstream oss;
        oss << "remove_front - cannot remove_front on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = array[front++];
    size --;
    return removedElement;
}

void Deque::insert_back(const EType &element) {
    checkBackCapacity();
    array[++back] = element;
    size ++;
}

EType Deque::remove_back(){
    if(size<=0){
        ostringstream oss;
        oss << "remove_back - cannot remove_back on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = array[back--];
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
    return array[front+index];
}

void Deque::setElement (int index, const EType &element){
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "setElement - out of bounds index (" << index << ") for array of size " << size;
        throw oss.str();
    }
    array[front+index] = element;
    return;
}

//Searching and sorting:

int Deque::find(const EType &element) const {
    for(int i=front; i <= back; i++){
        if(array[i]==element)
            return i - front;
        // returning i - front because that is the position of array[i] relative to the front
    }
    return -1;
    
}
bool Deque::search(const EType &element) const {
    if(find(element)==-1)
        return false;
    else
        return true;
}
void Deque::sort(){
    //priority queue
    priority_queue<int> pq;
    
    for (int i = front; i <= back; i++)
        pq.push(array[i]);
    
    for (int i = back; i >= front; i--) {
        array[i] = pq.top();
        pq.pop();
    }
}