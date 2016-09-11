#include <iostream>

#include "Node.h"
#include "Node_utils.h"

using namespace std;

int main() {
    Node *head = new Node(10);
    cout << *head << endl;
    
    cout<< "_______INSERT______" << endl;
    for(int i = 0; i < 50; i+=5){
        insert(head, i);
        print(cout, head);
        cout<<endl;
    }
    
    cout<< "_______REMOVE______" << endl;
    
    for(int i = 50; i > 0; i-=5){
        try{
            if (remove(head, i)){
                cout<< i << " removed." << endl;
                print(cout, head);
            }
            else
                cout << i << " not found.";
            cout<<endl;
        }
        catch(const char* e){
            cout << e << endl;
        }
    }
    return 0;
}
