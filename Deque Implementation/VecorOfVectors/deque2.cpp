#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include "deque2.h"
#include <vector>

using namespace std;

//CONSTRUCTOR:
Deque::Deque():capacity(10), size(0)
{
    // Allocate new memory for each subvector
    for(int i=0; i<capacity; i++)
        vec.push_back(new vector<EType>(SUB_VECT_CAPACITY));
    
    front.indexPos = capacity/2;
    front.subVectPos =  SUB_VECT_CAPACITY/ 2;
    back.indexPos = capacity/2;
    back.subVectPos = (SUB_VECT_CAPACITY / 2) -1;
    
    cout << "Deque created with capacity: " << capacity << " size: " << size << " front: " << front.indexPos << ' ' <<front.subVectPos << " back: " <<back.indexPos << ' ' << back.subVectPos  <<endl;
}


// To delete the subvectors
void Deque::uninit() {
    for(int i=0;i<capacity;i++)
        delete vec[i];
}


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
       // os << deque.vec.at(iStart)->at(jStart) <<  " ";
        
        if (iStart == iEnd) //only one subVect
            for (int j = jStart; j<=jEnd; j++){
                os << deque.vec.at(iStart)->at(j) <<  " ";
            }
       else{
            // print first subVect
            for( int j = jStart; j < SUB_VECT_CAPACITY; j++)
                 os << deque.vec.at(iStart)->at(j) <<  " ";
            // print middle subVects
            for (int i = (iStart + 1)%deque.capacity; i!=iEnd; i=(i+1)%deque.capacity){
                for (int j = 0; j < SUB_VECT_CAPACITY; j++){
                    os << deque.vec.at(i)->at(j) <<  "  ";
                }
            }
            // print last subVect
            for(int j = 0; j <= jEnd; j++){
                os << deque.vec.at(iEnd)->at(j) << " ";
            }
        }
        os << "}";
    }
    
    return os;
}


void Deque::doubleCapacity(){
    int oldCapacity = capacity;
    capacity*=2;
    vector<vector<EType> *> temp;
    
    for(int i=0; i<oldCapacity; i++){
        temp.push_back(vec.at(front.indexPos));
        front.indexPos = (front.indexPos+1)%oldCapacity;
    }
    for(int i = oldCapacity; i < capacity; i++){
        temp.push_back(new vector<EType>(SUB_VECT_CAPACITY));
    }
    vec = temp;
    front.indexPos = 0;
    back.indexPos = oldCapacity-1;
    cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;
}


void Deque::checkFrontCapacity(){
    if (front.subVectPos == 0) {
        if ( ((front.indexPos)-1 == back.indexPos) || (((front.indexPos)-1 <0) && (back.indexPos == capacity-1)) ){
            //copy to a bigger container because we're at the beginning of a subvector, and the subvector before is the subvector that back is in.
            std::cout<< std::endl << std::endl << "Need bigger vector" <<std::endl <<std::endl;
            doubleCapacity();
        }
    }
}


void Deque::checkBackCapacity(){
    if (back.subVectPos == SUB_VECT_CAPACITY - 1){
        if( ((back.indexPos)+1)%capacity == front.indexPos ){
            //copy to a bigger container because we're at the end of a subvector, and the next subvector is the subvector that front is in
            std::cout<< std::endl << std::endl << "Need bigger vector" <<std::endl <<std::endl;
            doubleCapacity();
        }
    }
}

 
// Insert element to front
void Deque::insert_front(const EType &element){
    checkFrontCapacity();
    // If front is at the beginning of a vector, move it to the end of the previous vector
    if (front.subVectPos == 0){
        front.indexPos --;
        if(front.indexPos<0)
            front.indexPos = capacity-1;
        front.subVectPos = SUB_VECT_CAPACITY -1;
    }
    else
        front.subVectPos --;
    
    vec.at(front.indexPos)->at(front.subVectPos) = element;
    
    size ++;
}


// Remove element from front, returns reference to removed element
EType& Deque::remove_front() {
    if(size<=0){
        ostringstream oss;
        oss << "remove_front - cannot remove_front on deque of size " << size;
        throw oss.str();
    }
    
    EType removedElement = vec.at(front.indexPos)->at(front.subVectPos);
    
    // If front is at sub_vect_cap-1, we need to move it to the beginning of the next vector
    if(front.subVectPos == SUB_VECT_CAPACITY-1) {
        front.subVectPos = 0;
        front.indexPos = (front.indexPos+1)%capacity;
    }
    else{
        front.subVectPos++;
    }
    size --;
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
    }
    else
        back.subVectPos ++;
    
    vec.at(back.indexPos)->at(back.subVectPos) = element;
 
    size ++;
}


EType& Deque::remove_back(){
    if(size<=0){
        ostringstream oss;
        oss << "remove_back - cannot remove_back on deque of size " << size;
        throw oss.str();
    }
    EType removedElement = vec.at(back.indexPos)->at(back.subVectPos);
    
    // If back is at 0, we need to move it to the end of the previous vector
    if(back.subVectPos == 0) {
        back.subVectPos = SUB_VECT_CAPACITY - 1;
        back.indexPos--;
        if(back.indexPos < 0) back.indexPos = capacity-1;
    }
    else{
        back.subVectPos--;
    }
    size --;
    return removedElement;
}

 
const EType& Deque::getFront() const {
    if (size == 0){
        ostringstream oss;
        oss << "the deque is empty";
        throw oss.str();
    }
    return vec.at(front.indexPos)->at(front.subVectPos);
}


const EType& Deque::getBack() const {
    if (size==0){
        ostringstream oss;
        oss << "the deque is empty";
        throw oss.str();
    }
    return vec.at(back.indexPos)->at(back.subVectPos);
}


const EType& Deque::getElement (int index) const {
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "getElement - out of bounds index (" << index << ") for deque with size" << size;
        throw oss.str();
    }
    int i = ((front.subVectPos + index)/SUB_VECT_CAPACITY + front.indexPos) % capacity;
    int j = (front.subVectPos + index)%SUB_VECT_CAPACITY;
    return vec.at(i)->at(j);
}


void Deque::setElement (int index, const EType &element){
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "setElement - out of bounds index (" << index << ") for deque of size " << size;
        throw oss.str();
    }
    int i = ((front.subVectPos + index)/SUB_VECT_CAPACITY + front.indexPos) % capacity;
    int j = (front.subVectPos + index)%SUB_VECT_CAPACITY;
    vec.at(i)->at(j) = element;
    return;
}
