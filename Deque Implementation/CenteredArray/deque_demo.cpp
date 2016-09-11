#include <iostream>
#include <cstdlib>

#include "deque.h"

using namespace std;

int main() {
    try {
        Deque deque (5);
        cout << "deque: " << deque << endl;
        
        //EXCEPTION HANDLING FOR REMOVE AND INSERT
        cout << "---- Testing some exception handling ----" << endl;
        try {
            deque.remove_back();
            throw "remove_back on empty array did NOT throw an exception";
        } catch (string s) {
        }
        try {
            deque.remove_front();		// should throw an exception
            throw "remove_front on empty array did NOT throw an exception";
        } catch (string s) {
        }
        try {
            deque.getElement(5);		// should throw an exception
            throw "getElement index > deque size did NOT throw an exception";
        } catch (string s) {
        }
        try {
            deque.setElement(-1,3);		// should throw an exception
            throw "setElement index < 0 did NOT throw an exception";
        } catch (string s) {
        }
        
        //INSERT_BACK
        cout << endl << "---- Testing insert_back ----" << endl;
        
        for (int i = 0; i < 15; i++){
            deque.insert_back(i);
            cout << deque <<endl;
        }
        
        //REMOVE_FRONT
        cout << endl << "---- Testing remove_front ----" << endl;
        
        while (deque.getSize() > 0) {
            cout << "Removing front element ... " << " removed " << deque.remove_front() << endl;
            cout << "deque: " << deque << endl;
        }
        
        //CONSTRUCTOR WITH DEFAULT PARAMETER
        cout << endl << "creating deque1 without sending it a capacity." << endl;
        Deque deque1;
        cout << "deque1: " << deque1 << endl;
        
        //INSERT_FRONT
        cout << endl << "---- Testing insert_front ____" << endl;

        for(int i = 0; i < 20; i++){
            cout << "Inserting element " << i << " at the front of the array ... " << endl;
            deque1.insert_front(i);
            cout << deque1 << endl;
        }
        cout << "deque1: " << deque1 << endl;
        
        //REMOVE_BACK
        cout << endl << "---- Testing remove_back ----" << endl;
        
        for (int i = 0; i < 10; i++){
            cout << "Removing last element ... " << " removed " << deque1.remove_back() << endl;
            cout << "deque1: " << deque1 << endl;
        }
        
        //FRONT
        cout << endl << "Checking out 'front': " << deque1.getFront() << endl;
        
        //BACK
        cout<< endl << "Checking out 'back': " << deque1.getBack() << endl;
       
        //SIZE
        cout << "size: " << deque1.getSize() << endl;
        
        //GET and SET
        cout << endl << deque1.getElement(5) << " is the fifth element" <<endl;
        cout << "Setting array[2] to 6" << endl;
        deque1.setElement(2, 6); // put into try ...
        cout << "deque1: " << deque1 << endl;
    
        //FIND and SEARCH
        cout << endl << "---- Testing find AND search ----" << endl;
        for (int i = 0; i < deque1.getSize()+4; i++){
            cout<<"Looking for element with value " << i << endl;
            bool found = (deque1.search(i));
            if(found)
                cout << "Found at index " << deque1.find(i);
            else
                cout<< "Element " << i << " not found. Find returns " << deque1.find(i);
            cout << endl; 
        }
        //SORT
        cout << endl << "---- Testing sort  ----" << endl;
        deque1.sort ();
        cout<<"The sorted deque1 is: " << endl << deque1 << endl;
        
        cout << "SUCCESS!" << endl;		
       
        
        return 0;
        
        
    } catch (string s) {
        cerr << "*** Exception caught: " << s << endl;
    } catch (const char *s) {
        cerr << "*** Exception caught: " << s << endl;
    }
}


