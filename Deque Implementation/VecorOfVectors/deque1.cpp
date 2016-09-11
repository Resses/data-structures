#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include "deque1.h"
#include <vector>

using namespace std;

//CONSTRUCTOR:
Deque::Deque():capacity(10), size(0) //10 sub-vectors, 0 elements
{
    arr = new vector<vector<EType> *>(capacity);
    // Allocate new memory for each subvector
    for(int i=0; i<capacity; i++)
        arr->at(i) = new vector<EType>(SUB_VECT_CAPACITY);
    
    front.indexPos = capacity/2;
    front.subVectPos =  SUB_VECT_CAPACITY/ 2;
    back.indexPos = capacity/2;
    back.subVectPos = (SUB_VECT_CAPACITY / 2) -1;
    cout << "Deque created with capacity: " << capacity << " size: " << size << " front: " << front.indexPos << ' ' <<front.subVectPos << " back: " <<back.indexPos << ' ' << back.subVectPos  <<endl;
}

/*
// Destructor -- THIS IS WRONG. SHOULD MAKE ONE...
Deque::~Deque()
{
    for(int i=0;i<capacity;i++)
        delete arr[i];
    delete[] arr;
}
*/

// << operator
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
            for (int j = jStart; j<=jEnd; j++){
                os << deque.arr->at(iStart)->at(j) <<  " ";
            }
        else{
            // print first subVect
            for( int j = jStart; j < SUB_VECT_CAPACITY; j++)
                 os << deque.arr->at(iStart)->at(j) <<  " ";
            // print middle subVects
            //os << "i = (iStart + 1)%deque.capacity is " << (iStart + 1)%deque.capacity;
            for (int i = (iStart + 1)%deque.capacity; i!=iEnd; i=(i+1)%deque.capacity){
                for (int j = 0; j < SUB_VECT_CAPACITY; j++){
                    os << deque.arr->at(i)->at(j) <<  "  ";
                }
            }
            // print last subVect
            for(int j = 0; j <= jEnd; j++){
                os << deque.arr->at(iEnd)->at(j) << " ";
            }
        }
        os << "}";
    }
    return os;
}


//PRIVATE:

void Deque::checkFrontCapacity(){
    if (front.subVectPos == 0) {
        if (   ((front.indexPos)-1 == back.indexPos) || (((front.indexPos)-1 <0) && (back.indexPos == capacity-1)) ){
            //copy to a bigger container
            std::cout<< std::endl << std::endl << "Need bigger array" <<std::endl <<std::endl;
            int oldCapacity = capacity;
            capacity*=2;
            
            vector<vector<EType> *> *temp = new vector<vector<EType> *>(capacity);
        
            for(int i=0; i<oldCapacity; i++){
                temp->at(i) = arr->at(front.indexPos);
                front.indexPos = (front.indexPos+1)%oldCapacity;
            }
            
            for(int i = oldCapacity; i < capacity; i++)
                temp->at(i) = new vector<EType>(SUB_VECT_CAPACITY);
           
            //delete[]arr; DOESNT WORK. WHY NOT??
            
            arr = temp;
            front.indexPos = 0;
            back.indexPos = oldCapacity-1;
            cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
        }
    }
}

void Deque::checkBackCapacity(){
 
    if (back.subVectPos == SUB_VECT_CAPACITY - 1){
        if( ((back.indexPos)+1)%capacity == front.indexPos ){

            //copy to a bigger container
            std::cout<< std::endl << std::endl << "Need bigger array" <<std::endl <<std::endl;
            int oldCapacity = capacity;
            capacity*=2;
            
            vector<vector<EType> *> *temp = new vector<vector<EType> *>(capacity);
            
            for(int i=0; i<oldCapacity; i++){
                temp->at(i) = arr->at(front.indexPos);
                front.indexPos = (front.indexPos+1)%oldCapacity;
            }
            for(int i = oldCapacity; i < capacity; i++)
                temp->at(i) = new vector<EType>(SUB_VECT_CAPACITY);
            

           // delete[]arr;
            arr = temp;
            front.indexPos = 0;
            back.indexPos = oldCapacity-1;
            cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
        }
    }
}


//PUBLIC:

 
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
    
    arr->at(front.indexPos)->at(front.subVectPos) = element;
    
    //arr[front.indexPos].size++; //the size of the sub vector is increasing
    size ++; //the # of elements in the deque is increasing
    
}


// Remove element from front, returns reference to removed element
EType& Deque::remove_front() {
    if(size<=0){
        ostringstream oss;
        oss << "remove_front - cannot remove_front on deque of size " << size;
        throw oss.str();
    }
    
    EType removedElement = arr->at(front.indexPos)->at(front.subVectPos);
    //arr[front.indexpos].size--; //the size of the sub vector its in is decreasing
    
    
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



void Deque::insert_back(const EType &element) {
    checkBackCapacity();
    
    // If back is at the end of a vector, move it to the beginning of the next vector
    if (back.subVectPos == SUB_VECT_CAPACITY -1){
        back.indexPos ++;
        if(back.indexPos >= capacity){
            back.indexPos = 0;
            std::cout << back;
        }
        back.subVectPos = 0;
        //arr.size++; //#of sub vectors is increasing
    }
    else
        back.subVectPos ++;
    
    arr->at(back.indexPos)->at(back.subVectPos) = element;
 
    size ++;
  
}



EType& Deque::remove_back(){
    if(size<=0){
        ostringstream oss;
        oss << "remove_back - cannot remove_back on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = arr->at(back.indexPos)->at(back.subVectPos);
    
    
    // If back is at 0, we need to move it to the end of the previous vector
    if(back.subVectPos == 0) {
        back.subVectPos = SUB_VECT_CAPACITY - 1;
        back.indexPos--;
        if(back.indexPos < 0) back.indexPos = capacity-1;
        //# of sub vectors decreases? but not really?
        //arr.size--;
    }
    else{
        back.subVectPos--;
    }
    size --;//the # of elements in the deque is decreasing
    return removedElement;
}


//Accessors and mutator:
 
const EType& Deque::getFront() const {
    if (size == 0){
        ostringstream oss;
        oss << "the deque is empty";
        throw oss.str();
    }
    return arr->at(front.indexPos)->at(front.subVectPos);
}

const EType& Deque::getBack() const {
    if (size==0){
        ostringstream oss;
        oss << "the deque is empty";
        throw oss.str();
    }
    return arr->at(back.indexPos)->at(back.subVectPos);
}



const EType& Deque::getElement (int index) const {
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "getElement - out of bounds index (" << index << ") for deque with size" << size;
        throw oss.str();
    }
    int i = ((front.subVectPos + index)/SUB_VECT_CAPACITY + front.indexPos) % capacity;
    int j = (front.subVectPos + index)%SUB_VECT_CAPACITY;
    return arr->at(i)->at(j);
}

void Deque::setElement (int index, const EType &element){
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "setElement - out of bounds index (" << index << ") for deque of size " << size;
        throw oss.str();
    }
    int i = ((front.subVectPos + index)/SUB_VECT_CAPACITY + front.indexPos) % capacity;
    int j = (front.subVectPos + index)%SUB_VECT_CAPACITY;
    arr->at(i)->at(j) = element;
    return;

}



