#pragma once
#include "Neiron.h"

using namespace std;

class Population {
private:
	vector<Neiron*> pop;
	double mutationPer = 1; //0.01  //0.07
	double maxMutper = 0.03;  //0.05   //0.17
	int Size;

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

	int layers = 2;
	int* newirons = new int[layers];
	
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

	void CreateNew();

};