//This file contains the function implementations(bodies)

#include <iostream>
#include <sstream>
#include <queue>

#include "resizeable.h"

using namespace std;

//PRIVATE:

//capacity management:

void Sequence::check_capacity(){
	if (size >= capacity) {
		int oldCapacity = capacity;
		capacity*=2;
		EType *temp = new EType[capacity];
		for (int i = 0; i < size; i++)
			temp[i]=array[i];
		delete[]array;
		array = temp;
		cerr << "The capacity was doubled from " << oldCapacity << " to " << capacity << endl;	
	}
}

//PUBLIC:

//insert and remove:

void Sequence::insert_back(const EType &element) {
	check_capacity();
	array[size++] = element;
}
EType Sequence::remove_back(){
	if(size<=0){
		ostringstream oss;
		oss << "remove_back - cannot remove_back on sequence of size " << size;
		throw oss.str();
	}
	EType removedElement = array[size-1];
	size--;
	return removedElement; 
}
void Sequence::insert(int index, const EType &element){	
	check_capacity();
	if (index < 0 || index > size) {
		ostringstream oss;
		oss << "insert - out of bounds index (" << index << ") for array of size " << size;
		throw oss.str();
	}
	size++;
	for(int i = size-1; i > index; i--)
		array[i]=array[i-1]; 
	array[index]=element;
}
EType Sequence::remove(int index) {
	if (index < 0 || index >= size) {
		ostringstream oss;
		oss << "remove - out of bounds index (" << index << ") for array of size " << size;
		throw oss.str();
	}
	EType removedElement = array[index];
	for (int i = index; i < size-1; i++)
		array[i] = array[i+1];
	size--;
	return removedElement;
}
void Sequence::insert_front(const EType &element){
	insert(0,element);
}
EType Sequence::remove_front() {return remove(0);}

//Accessors and mutator:

const EType& Sequence::front() const {return array[0];}
const EType& Sequence::back() const {return array[size-1];}
int Sequence::getSize() const {return size;}
const EType& Sequence::getElement (int index) const {
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "getElement - out of bounds index (" << index << ") for array of size " << size;
        throw oss.str();
    }
    return array[index];
}
void Sequence::setElement (int index, const EType &element){
    if (index < 0 || index >= size) {
        ostringstream oss;
        oss << "setElement - out of bounds index (" << index << ") for array of size " << size;
        throw oss.str();
    }
    array[index] = element;
    return;
};

//Searching and sorting:

int Sequence::find(const EType &element) const {
	for(int i=0; i < size; i++){
		if(array[i]==element)
			return i;
	}
	return -1;
	
}
bool Sequence::search(const EType &element) const {
	if(find(element)==-1)
		return false;
	else 
		return true;
}
void Sequence::sort(){
//priority queue
    priority_queue<int> pq;
    
    for (int i = 0; i < size; i++)
        pq.push(array[i]);
    
    for (int i = size-1; i >= 0; i--) {
        array[i] = pq.top();
        pq.pop();
    }
}

/*Bubble Sort:
	for (int last = size-1; last > 0; last--) {
		for (int i = 0; i < last; i++)
			if (array[i] > array[i+1]){
				EType t = array[i];
				array[i] = array[i+1];
				array[i+1] = t;
			}
	}
*/
