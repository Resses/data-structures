#include <iostream>
#include <cstdlib>

#include "resizeable.h"

using namespace std;

int main() {
	try {
		Sequence sequence;
		cout << "sequence: " << sequence << endl;

	//EXCEPTION HANDLING FOR REMOVE AND INSERT
		cout << "---- Testing some exception handling ----" << endl;
		try {
			sequence.remove(0);		// should throw an exception
			throw "remove from empty sequence did NOT throw an exception";
		} catch (string s) {
		}

		try {
			sequence.remove(-1);		// should throw an exception
			throw "remove using negative index did  NOT throw an exception";
		} catch (string s) {
		}
		try {
			sequence.remove_back(); 
			throw "remove_back on empty array did NOT throw an exception";
		} catch (string s) {
		}
		try {
			sequence.insert(-1, 5);		// should throw an exception
			throw "insert into negative index did NOT throw an exception";
		} catch (string s) {
		}

		try {
			sequence.insert(1, 5);		// should throw an exception
			throw "insert into index > sequence size did NOT throw an exception";
		} catch (string s) {
		}
        try {
            sequence.getElement(5);		// should throw an exception
            throw "getElement index > sequence size did NOT throw an exception";
        } catch (string s) {
        }
        try {
            sequence.setElement(-1,3);		// should throw an exception
            throw "setElement index < 0 did NOT throw an exception";
        } catch (string s) {
        }
	
	//INSERT_BACK
		cout << endl << "---- Testing insert_back ----" << endl;

		for (int i = 0; i < 15; i++)
			sequence.insert_back(i);

		cout << "sequence: " << sequence <<endl;
	
	//FRONT
		cout << endl << "Checking out 'front': " << sequence.front() << endl;

	//BACK
		cout<< endl << "Checking out 'back': " << sequence.back() << endl;
		cout << "size: " << sequence.getSize() << endl;
    //Get and Set element
        cout << endl << sequence.getElement(5) << " is the fifth element" <<endl;
        cout << "Setting array[3] to 6" << endl;
        sequence.setElement(3, 6);
        cout << "sequence: " << sequence << endl;
	//REMOVE
		cout << endl << "---- Testing remove ----" << endl;
	
		cout << "sequence: " << sequence << endl;
		while (sequence.getSize () > 0){
			int index = rand() % sequence.getSize();
			cout << "Removing element at index: " << index << " ... " << " removed " << sequence.remove(index) << endl;
			cout << "sequence: " << sequence << endl;
		}
	//REMOVE_FRONT
		cout << endl << "---- Testing remove_front ----" << endl;

		for (int i = 0; i < 10; i++)
			sequence.insert_back(i);

		cout << "sequence: " << sequence << endl;

		while (sequence.getSize() > 0) {
			cout << "Removing front element ... " << " removed " << sequence.remove_front() << endl;
			cout << "sequence: " << sequence << endl;
		}

	//REMOVE_BACK		
		cout << endl << "---- Testing remove_back ----" << endl;
	
		for (int i = 0; i < 10; i++)
			sequence.insert_back(i);

		cout << "sequence: " << sequence << endl;

		while (sequence.getSize() > 0) {
			cout << "Removing last element ... " << " removed " << sequence.remove_back() << endl;
			cout << "sequece: " << sequence << endl;
		}

	//INSERT 
		cout << endl << "---- Testing insert ----" << endl;

		for (int i = 0; i < 25; i++)
			sequence.insert_back(i);

		cout << "sequence: " << sequence << endl;

		for (int i=0; i<5;i++) {//insert 5 elements at random locations
			int index = rand() % sequence.getSize();
			cout << "Inserting element "<<i<<" at index: " << index << " ... " << endl;
			sequence.insert(index, i);
			cout << "sequence: " << sequence << endl;
		}
	
		int index = sequence.getSize();
		cout << "Inserting element " << index << " at index " << index << " which is the end of the array" <<endl;
		sequence.insert(index, index); 
		cout << "sequence: " << sequence << endl;	
		
	//INSERT_FRONT
		cout << endl << "---- Testing insert_front ____" << endl;
		try{
			sequence.insert_front(5);
		}
		catch (string s){
			cout << s << endl;
		}	
		while (sequence.getSize() > 0){
			sequence.remove_back();
		}
		cout<< "sequence: " << sequence << endl;
		for(int i = 0; i < 10; i++){
			cout << "Inserting element "<<i<<" at the front of the array ... " << endl;
			try{
				sequence.insert_front(i);
			}
			catch(string s){
				cout << s << endl;
			}
			cout << "sequence: " << sequence << endl;
		}
		//clear array and then insert at front 
		while(sequence.getSize() > 0)
			sequence.remove_back();	
		cout << "The sequence was cleared. " <<endl;
		cout << "sequence: " << sequence << endl;
		for(int i=0; i < 10; i++)
			sequence.insert_front(i);
		cout<< "Inserted ten elements: "<<endl;	
		cout<<"The front element is: " << sequence.front() << endl;
		cout << "sequence: " << sequence << endl;

	//FIND and SEARCH
		cout << endl << "---- Testing find AND search ----" << endl;
		for (int i = 0; i < sequence.getSize()+4; i++){
			cout<<"Looking for element " << i << endl;
			bool found = (sequence.search(i));
			if(found)
				cout << "Found at index " << sequence.find(i); 
			else
				cout<< "Element " << i << " not found. Find returns " << sequence.find(i);
			cout << endl; 
		}
	//SORT
		cout << endl << "---- Testing sort  ----" << endl;
		sequence.sort ();
		cout<<"The sorted sequence is: " << endl << sequence << endl;	
		
		cout << "SUCCESS!" << endl;		
		return 0;


	} catch (string s) {
		cerr << "*** Exception caught: " << s << endl;
	} catch (const char *s) {
		cerr << "*** Exception caught: " << s << endl;
	}
}


