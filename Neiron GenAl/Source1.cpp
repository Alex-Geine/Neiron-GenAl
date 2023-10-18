#include "Population.h"
#include <iostream>

using namespace std;

void main() {
	Population p(500);
	for (int i = 0; i < 10000; i++) {
		
			p.Selection();
			
			p.Crossing();			
			p.Selection();
			p.Mutations();
			p.CreateNew();
			   
		cout << p.fsr << "  Best f" << p.best << endl;
		if (p.best <= 0.05) {
			p.Best->Result();
			cout << "Iterations: " << i << endl;
			i = 1000000;
		}
			
	}
	
}