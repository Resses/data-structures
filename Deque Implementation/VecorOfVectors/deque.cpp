#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include "deque.h"

using namespace std;

//CONSTRUCTOR:
Deque::Deque():capacity(10), size(0)
{
    arr = new DataVector*[capacity]; //in stead of  arr(new DataVector*[capacity])
    // Allocate new data vector memory
    for(int i=0; i<capacity; i++)
        arr[i] = new DataVector();
    
    front.indexPos = capacity/2;
    front.subVectPos =  SUB_VECT_CAPACITY/ 2;
    back.indexPos = capacity/2;
    back.subVectPos = (SUB_VECT_CAPACITY / 2) -1;
    cout << "Deque created with capacity: " << capacity << " size: " << size << " front: " << front.indexPos << ' ' <<front.subVectPos << " back: " <<back.indexPos << ' ' << back.subVectPos  <<endl;
}

// Destructor
Deque::~Deque()
{
    for(int i=0;i<capacity;i++)
        delete arr[i];
    delete[] arr;
}

// << operator
/*
std::ostream &operator <<(std::ostream &os, const Deque &deque) {
    os << "F: " << deque.front << " B: " << deque.back << " ... ";
    os << '{';
    if(deque.size == 0)
        os << " }";
    else{
        int iStart = deque.front.indexPos;
        int iEnd = deque.back.indexPos;
        int jStart = deque.front.subVectPos;
        int jEnd = deque.back.subVectPos;
        
        if (iStart == iEnd) //only one subVect
            for (int j = jStart; j<jEnd; j++){
                os << deque.arr[iStart][j] <<  "  ";
            }
        else{
            // print first subVect
            for( int j = jStart; j < deque.SUB_VECT_CAPACITY; j++)
                 os << deque.arr[iStart][j] <<  "  ";
            // print middle subVects
            for (int i = (iStart + 1)%capacity; i< iEnd - 1; i++){
                for (int j = 0; j < deque.SUB_VECT_CAPACITY; j++){
                    os << deque.arr[i][J] <<  "  ";
                }
            }
            // print last subVect
            for(int j = 0; j < jEnd; j++){
                os << deque.arr[iEnd][j];
            }
        }
        os << "}";
    }
    return os;
}

*/
//PRIVATE:

void Deque::checkFrontCapacity(){
    if (front.subVectPos == 0) {
        if (   ((front.indexPos)-1 == back.indexPos) || (((front.indexPos)-1 <0) && (back.indexPos == capacity-1)) ){
            //copy to a bigger container
            int oldCapacity = capacity;
            capacity*=2;
            DataVector **temp = new DataVector*[capacity];
            for(int i = 0; i<oldCapacity; i++)
                temp[i] = arr[front.indexPos++];
            delete[]arr;
            arr = temp;
            front.indexPos = 0;
            back.indexPos = oldCapacity-1;
            cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
        }
    }
}

void Deque::checkBackCapacity(){
    if (back.subVectPos == SUB_VECT_CAPACITY){
        if( ((back.indexPos)+1)%capacity == front.indexPos ){
            //copy to a bigger container
            int oldCapacity = capacity;
            capacity*=2;
            DataVector **temp = new DataVector*[capacity];
            for(int i = 0; i<oldCapacity; i++)
                temp[i] = arr[front.indexPos++];
            delete[]arr;
            arr = temp;
            front.indexPos = 0;
            back.indexPos = oldCapacity-1;
            cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
        }
    }
}

//PUBLIC:

//insert and remove:
// Insert element to front
void Deque::insert_front(const EType &element){
    checkFrontCapacity();
    
    // If front is at the beginning of a vector, move it to the end of the previous vector
    if (front.subVectPos == 0){
        front.indexPos --;
        if(front.indexPos<0)
            front.indexPos = capacity-1;
        front.subVectPos = SUB_VECT_CAPACITY -1;
        //arr.size++; //#of sub vectors is increasing
    }
    else
        front.subVectPos --;
    
    arr[front.indexPos][front.subVectPos] = element;
    
    arr[front.indexPos].size++; //the size of the sub vector is increasing
    size ++; //the # of elements in the deque is increasing
}

// Remove element from front, returns reference to removed element
EType& Deque::remove_front() {
    if(size<=0){
        ostringstream oss;
        oss << "remove_front - cannot remove_front on deque of size " << size;
        throw oss.str();
    }
    
    EType removedElement = array[front.indexPos][front.subVectPos];
    arr[front.indexpos].size--; //the size of the sub vector its in is decreasing
    
    
    // If front is at sub_vect_cap-1, we need to move it to the beginning of the next vector
    if(front.subVectPos == SUB_VECT_CAPACITY-1) {
        front.subVectPos = 0;
        front.indexPos = (front.indexPos+1)%capacity;
        //# of sub vectors decreases? but not really?
        //arr.size--;
    }
    else{
        front.subVectPos++;
    }
    size --;//the # of elements in the deque is decreasing
    return removedElement;
}
/*
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
*/
//Accessors and mutator:

const EType& Deque::getFront() const {
    if (size == 0){
        ostringstream oss;
        oss << "the array is empty";
        throw oss.str();
    }
    return array[front.indexPos][front.subVectPos];
}

const EType& Deque::getBack() const {
    if (size==0){
        ostringstream oss;
        oss << "the array is empty";
        throw oss.str();
    }
    return array[back.indexPos][back.subVectPos];
}

int Deque::getSize() const {return size;}

const EType& Deque::getElement (int index) const {
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "getElement - out of bounds index (" << index << ") for array with size" << size;
        throw oss.str();
    }
    int i = (front.subVectPos + index)/SUB_VECT_CAPACITY + front.indexPos;
    int j = (front.subVectPos + index)%SUB_VECT_CAPACITY;
    return array[i][j];
}

/*
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

*/


/*
 //capacity management:
 void Deque::checkCapacity(){
 if (size == SUB_VECT_CAPACITY *capacity){ //it is full
 int oldCapacity = capacity;
 capacity*=2;
 DataVector **temp = new DataVector*[capacity];
 //need to copy from front to back, and wrap around
 int i = ...
 while(!((front.indexPos==back.indexPos)&&(front.subVectPos==back.subVectPos))){
 for(int j=0; j< SUB_VECT_CAPACITY; j++){
 temp[i][j] = arr[front.indexPos][front.subVectPos];
 if(front.subVectPos==SUB_VECT_CAPACITY-1){
 if(front.indexPos==capacity-1)
 front.indexPos==0;
 else
 front.indexPos++;
 front.subVectPos==0;
 }
 else
 front.subVectPos++;
 }
 }
 for (int i = 0; i < size; i++)
 temp[i]=array[i];
 delete[]array;
 array = temp;
 cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
 
 }
 }
*/