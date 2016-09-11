#include <iostream>

#include "deque.h"

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
    
    for (int i = 0; i < 30; i++) {
        deque2.insert_back(i);
        cout << "After insert_back(" << i << "): " << deque2 << endl;
    }
    
    while (!deque2.empty())
        cout << "After remove_front of " << deque2.remove_front() << ": " << deque2 << endl;
    
    cout << endl << endl << "------ Inserting at the front -----" << endl << endl;
    
    Deque deque3;
    
    for (int i = 0; i < 30; i++) {
        deque3.insert_front(i);
        cout << "After insert_front(" << i << "): " << deque3 << endl;
    }
    
    while (!deque3.empty()) 
        cout << "After remove_back of " << deque3.remove_back() << ": " << deque3 << endl;
    
    return 0;
}
