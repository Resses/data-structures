#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <iostream>

#include "Node.h"

//functions for sorted list
void insert(Node *&head, EType &val);
bool remove(Node *&head, EType &val);

void print(std::ostream &os, const Node *head);

#endif