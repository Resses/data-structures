
#include "linked_list.h"

ostream &operator <<(ostream &os, const LinkedList &linkedList) {
    os << "{";
    Node *p = linkedList.head;
    p=p->next;
    while (p!= linkedList.head) {
        os << p->data << (p->next!=linkedList.head ? ", " : "");
        p = p->next;
    }
    os << "}";
    return os;
}

///////Do I need data in head???????

LinkedList::LinkedList () : head(new Node(-1)) {
    head->next = head;
    head->prev = head;
    size=0;
}


void LinkedList::insert(Node *p, const EType &data) {
    if(!p)
        throw "p does not exist";
   // if(p==head)
     //   throw "Cannot change header ";
    if(!(p->prev))
        throw "p does not have a left neighbor. Error.";
    Node* newNode = new Node (data);
    Node *leftN = p->prev;
    newNode->next = p;
    newNode->prev = leftN;
    p->prev = newNode;
    leftN->next = newNode;
    size++;
}

EType LinkedList::remove(Node *p){
    if(!p)
        throw "p does not exist";
    //There should always be a next and previous of a node in a circular list
    if(!(p->prev))
        throw "p does not have a left neighbor. Error.";
    if(!(p->next))
        throw "p does not have a right neighbor. Error.";

    if(p==head)
       throw "cannot remove header node";
    
    EType data = p->data;
    Node *leftN = p->prev;
    Node *rightN = p->next;
    leftN->next = rightN;
    rightN->prev = leftN;
    delete p;
    size--;
    return data;
}

bool LinkedList::remove(const EType &val){
    Node *p = head;
    while(p){
        if (p->data == val){
            remove(p);
            return true;
        }
        else
           p = p->next;
    }
        return false;
}


