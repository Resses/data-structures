#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <iostream>

#include "Node.h"
#include "Node_utils.h"

using namespace std;

void insertFront(Node *&head, const EType &data) {
    if (!head) throw "null pointer sent to insertFront";
    head = new Node(data, head);
}

void insertAfter(Node *nodeP, const EType &val) {
    if (!nodeP) throw "Passed NULL to insertAfter";
    Node *newNodeP = new Node(val, nodeP->next);
    nodeP->next = newNodeP;
}

void insert(Node *&head, EType &val){
    Node *p = head;
    Node *q = 0;
    while (p && val > p->data){
        q = p;
        p = p->next;
    }
    if(q)
        insertAfter(q, val);
    else
        insertFront(head, val);
}

EType removeFront(Node *&head) {
    if (!head) throw "Attempt to remove first element of empty list";
    Node *hold = head;
    head = head->next;
    EType data = hold->data;
    delete hold;
    return data;
}

EType removeAfter(Node *nodeP) {
    if (!nodeP) throw "Passed NULL to removeAfter";
    if (!nodeP->next) throw "Attempting to remove nonexistent node";
    Node *nextNodeP = nodeP->next;
    nodeP->next = nextNodeP->next;
    EType data = nextNodeP->data;
    delete nextNodeP;
    return data;
}

bool remove(Node *&head, EType &val){
    Node *p = head;
    Node *q = 0;
    while(p){
        if(p->data == val){
            if(!q)
                removeFront(head);
            else
                removeAfter(q);
            return true;
        }
        else{
            q = p;
            p = p->next;
        }
    }
    return false;
}

void print(ostream &os, const Node *head) {
    while (head) {
        os << *head;
        head = head->next;
    }
}

#endif