#include "Population.h"
#include <iostream>

using namespace std;

void main() {
	Population p(100);
	for (int i = 0; i < 10000; i++) {
		
			p.Selection();
			p.Crossing();
			p.Mutations();
		
		cout << p.fsr << "  Best f" << p.best << endl;
		if (p.best <= 0.1) {
			p.Best->Result();
			i = 1000000;
		}
			
	}
}