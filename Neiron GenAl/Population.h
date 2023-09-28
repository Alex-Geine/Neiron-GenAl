#pragma once
#include "Neiron.h"

using namespace std;

class Population {
private:
	vector<Neiron*> pop;
	double mutationPer = 0.07; //0.01  //0.07
	double maxMutper = 0.7;  //0.05   //0.17

	double Table[8][3] = {
		{0,0,0},
		{0,0,1},
		{0,1,0},
		{0,1,1},
		{1,0,0},
		{1,0,1},
		{1,1,0},	
		{1,1,1}
	};

public:
	

	double fsr;
	double best;
	Neiron* Best;
	Population(int count);

	//Функция отбора особей
	void Selection();

	//Функция скрецивания
	void Crossing();

	//Функция мутации
	void Mutations();

};