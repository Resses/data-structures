#include <iostream>

#include "deque2.h"

using namespace std;

int main() {
    
    Deque deque1;
    
    cout << "Initially created: " << deque1 << endl;
    
    cout << endl << "------ Alternating insertions -------------" << endl << endl;
    
    for (int i = 0; i < 30; i++)
        if (i % 2 == 0) {
            deque1.insert_front(i);
            cout << "After insert_front(" << i << "): " << deque1 << endl;
        }
        else {
            deque1.insert_back(i);
            cout << "After insert_back(" << i << "): " << deque1 << endl;
        }
  
    while (!deque1.empty())
        if (deque1.getSize() % 2 == 0)
            cout << "After remove_front of " << deque1.remove_front() << ": " << deque1 << endl;
        else
            cout << "After remove_back of " << deque1.remove_back() << ": " << deque1 << endl;;
   
    cout << endl << endl << "------ Inserting at the back -----" << endl << endl;
    
    Deque deque2;
    
    for (int i = 0; i < 100; i++) {
        deque2.insert_back(i);
        cout << "After insert_back(" << i << "): " << deque2 << endl;
    }
    
    while (!deque2.empty())
        cout << "After remove_front of " << deque2.remove_front() << ": " << deque2 << endl;
    
    cout << endl << endl << "------ Inserting at the front -----" << endl << endl;
    
    Deque deque3;
    
    for (int i = 0; i < 100; i++) {
        deque3.insert_front(i);
        cout << "After insert_front(" << i << "): " << deque3 << endl;
    }
    
    cout<< "The front of the deque is " << deque3.getFront() << endl;
    cout<< "The back of the deque is " << deque3.getBack() << endl;
    cout<< "The size of the deque is " << deque3.getSize() << endl;
    cout << "The 13th element is " <<deque3.getElement(13) <<endl;
    deque3.setElement(13, 3333333);
    cout << "Changed it to 3333333: " <<deque3 << endl;
    

    
    while (!deque3.empty())
        deque3.remove_back();
    cout << "after removing all: " << deque3 << endl;
    
    cout << "SUCCESS!" << endl;
    
    return 0;
}

