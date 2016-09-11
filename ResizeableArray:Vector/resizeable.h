//This file contains the function headers

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>

typedef int EType;

class Sequence {
	friend std::ostream &operator <<(std::ostream &os, const Sequence &sequence) {
		os << '{';
		for (int i = 0; i < sequence.size; i++)
			os << sequence.array[i] << (i < sequence.size -1 ? ", " : "");
		os << "}";
		return os;
	}
	public:
        //constructor
		Sequence() : size(0), capacity(10), array(new EType[capacity]) {}
    
        //insert and remove
		void insert_back(const EType &element);
		EType remove_back();
		void insert (int index, const EType &element);
		EType remove(int index);
		void insert_front (const EType &element);
		EType remove_front();
    
        //accessors and mutator
		const EType &front()const;
		const EType &back()const;
        int getSize() const;
        const EType &getElement (int index) const;
        void setElement (int index, const EType &element);

        //searching and sorting
        int find(const EType &element)const;
        bool search(const EType &element)const;
        void sort();

    private:
        //variables
		int capacity; 
		int size;
		EType *array;
    
        //functions
		void check_capacity();
};
#endif
