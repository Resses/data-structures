#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

#include "Node.h"

using namespace std;

class LinkedList {

    friend ostream &operator << (ostream &os, const LinkedList &linkedList);

public:

    LinkedList();
    void insert(Node *p, const EType &data);
    EType remove(Node *p);
    bool remove(const EType &val);
    int getSize() { return size; }
    bool empty() { return (size==0); }
    
    Node* getHead () const {return head; }
    Node* getFront () const {return head->next; }
    Node* getBack () const {return head->prev; }
    
private:
    int size;
    Node *head;
    
};

#endif
