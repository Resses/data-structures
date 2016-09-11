#include <iostream>
#include <cstdlib>
 
#include "resizeable.h"
 
using namespace std;
 
int main() {
	Sequence sequence;
	int j;
	long total=0;
	
	while (cin >> j){
		sequence.insert_back(j);
		total += j;
	}
	long average = total / sequence.getSize();
	int counter = 0;
	for (int i = 0; i < sequence.getSize(); i ++)
		if (sequence.getElement(i) < average)
			counter ++;
	cout << "total: " << total << " size: " << sequence.getSize() << endl;
	cout << "The average is " << average << endl;
	cout << "The number of values less than the average is " << counter << endl;
	return 0;
}
