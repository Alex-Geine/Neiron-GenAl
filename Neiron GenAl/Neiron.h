#pragma once

#include <time.h>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;


class Neiron {
   
private:
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

    int layers;
    int* neironsCount;
    double** koef;
    double*** w;
    double** x;

    double B = 1;

    //функция активации
    double Function(double S);

    //перебор слоя
    void LayerFunc(int layer);  
public:
    double f = 1;
    //конструктор
    Neiron(int layers, int* neironsCount);

    //деструктор
    ~Neiron();  

    //вывод результатов работы сети
    double Work(double x1, double x2, double x3);

    //метод скрещивания двух неиросетей
    Neiron* Cross(Neiron* parent);

    //метод для мутации
    Neiron* Mutation( double per);

    //Функция вывода реультата
    void Result();
};