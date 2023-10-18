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

    //������� ���������
    double Function(double S);

    //������� ����
    void LayerFunc(int layer);  
public:
    double f = 1;
    //�����������
    Neiron(int layers, int* neironsCount);

    //����������
    ~Neiron();  

    //����� ����������� ������ ����
    double Work(double x1, double x2, double x3);

    //����� ����������� ���� ����������
    Neiron* Cross(Neiron* parent);

    //����� ��� �������
    Neiron* Mutation( double per);

    //������� ������ ���������
    void Result();
};