#include <iostream>

#include "Node.h"
#include "linked_list.h"

using namespace std;

int main(){
    LinkedList list;
    cout << list <<endl;
    
    list.insert(list.getHead(), 5);
    list.insert(list.getHead(), 7);
    list.insert(list.getFront(), 3);
    cout << list <<endl;
    try {
        list.remove(list.getHead());
    }catch(const char* e){
        cout << e << endl;
    }
    try {
        int x= list.remove(list.getBack());
        cout << x << " was removed." << endl;
    }catch(const char* e){
        cout << e << endl;
    }
    cout << "The size of the list is " << list.getSize() << endl;
    while (!list.empty()){
        cout << list << endl;
        list.remove(list.getFront());
    }
    cout << list << " list is empty" << endl;
    return 0;
}