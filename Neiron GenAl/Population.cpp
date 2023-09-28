#include "Population.h"
#include <algorithm>

Population::Population(int count) {
	int layers = 2;
	int* newirons = new int[layers];
	newirons[0] = 4;
	newirons[1] = 1;

	for (int i = 0; i < count; i++) {
		Neiron *n = new Neiron(layers, newirons);
		pop.push_back(n);
	}
}

//Функция отбора особей
void Population::Selection() {
	random_shuffle(pop.begin(), pop.end());
	vector<Neiron*> del;

	//турнирный отбор
	for (int i = 0; i < pop.size(); i += 2) {
		if (pop.size() - i != 1) {
			double f1 = 0, f2 = 0;

			for (int j = 0; j < 8; j++) {
				double y = (double)(
					(bool)Table[j][0] ^
					(bool)Table[j][1] ^
					(bool)Table[j][2]
					);
				double yy1 = pop[i]->Work(
					Table[j][0],
					Table[j][1],
					Table[j][2]);
				double yy2 = pop[i + 1]->Work(
					Table[j][0],
					Table[j][1],
					Table[j][2]);

				f1 += fabs(yy1 - y);
				f2 += fabs(yy2 - y);

			}
			if ((f1 == 0) || (f2 == 0)) {
				cout << "hernia" << endl;
				for (int j = 0; j < 8; j++) {
					double y = (double)(
						(bool)Table[j][0] ^
						(bool)Table[j][1] ^
						(bool)Table[j][2]
						);
					double yy1 = pop[i]->Work(
						Table[j][0],
						Table[j][1],
						Table[j][2]);
					double yy2 = pop[i + 1]->Work(
						Table[j][0],
						Table[j][1],
						Table[j][2]);

					f1 += fabs(yy1 - y);
					f2 += fabs(yy2 - y);

				}
			}
			pop[i]->f = f1 / 8;
			pop[i + 1]->f = f2 / 8;

			if (f1 > f2)
				del.push_back(pop[i]);
			else
				del.push_back(pop[i + 1]);
		}
	}

	//удаление ненужных особей
	 for (int i = 0; i < del.size(); i++) {
		auto iter = pop.begin();
		for (int j = 0; j < pop.size(); j++) {			
			if (del[i] == pop[j]) {
				iter += j;
				pop.erase(iter);
				j = pop.size() + 1;
			}
		}		
	}
	//поиск средней приспособленности по ансамблю
	 double sum = 0;
	 best = 1;
	 for (int i = 0; i < pop.size(); i++) {
		 sum += pop[i]->f;
		 if (pop[i]->f < best) {
			 best = pop[i]->f;
			 Best = pop[i];
		 }
	 }
	 
	this->fsr = sum / pop.size();

	del.clear();
}

//Функция скрецивания
void Population::Crossing() {
	vector<Neiron*> n;	

	//поиск особей для скрещивания
	for (int i = 0; i < pop.size(); i++)
			n.push_back(pop[i]);
		
	while (pop.size() <= 100) {
		random_shuffle(n.begin(), n.end());
		for (int i = 0; i < n.size(); i++) {
			if (n.size() - i != 1) {				
				vector<Neiron*> vec = (n[i]->Cross(n[i + 1]));				
				pop.push_back(vec[0]);
				pop.push_back(vec[1]);
			}
			if (pop.size() >= 100)
				i = n.size();
		}		
	}
	n.clear();
}

//Функция мутации
void Population::Mutations() {
	int Size = pop.size();
	for (int i = 0; i < Size; i++) {
		double ran = (double)rand() / RAND_MAX;
		if (ran <= mutationPer) 					
			pop.push_back(pop[i]->Mutation(maxMutper));		
	}

}